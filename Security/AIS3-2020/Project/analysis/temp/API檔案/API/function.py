import pandas as pd
from keras.models import load_model
from tensorflow import keras
import jieba_fast.posseg as pseg

class LSTM_Model:
    def __init__(self):
        # 載入模型
        self.model = load_model('my_model.h5')

    def query(self, title, content):
        
        def jieba_tokenizer(text):
            words = pseg.cut(text)
            return ' '.join([word for word, flag in words if flag != 'x'])

        tt = title
        aa = content
        data = {'title': [tt], 'content': [aa]}
        myframe = pd.DataFrame(data)

        myframe['title_tokenized'] = myframe.loc[:, 'title'].apply(jieba_tokenizer)
        myframe['content_tokenized'] = myframe.loc[:, 'content'].apply(jieba_tokenizer)

        test_x1 = myframe.title_tokenized
        test_x2 = myframe.content_tokenized
        corpus = pd.concat([test_x1, test_x2])

        MAX_SEQUENCE_LENGTH1 = 20
        MAX_SEQUENCE_LENGTH2 = 5000

        MAX_NUM_WORDS = 5000  # 最高不超過 5000 個詞彙
        tokenizer = keras.preprocessing.text.Tokenizer(num_words=MAX_NUM_WORDS)

        # 將詞彙序列轉為索引數字的序列
        tokenizer.fit_on_texts(corpus)
        x1_test = tokenizer.texts_to_sequences(test_x1)  # title
        x2_test = tokenizer.texts_to_sequences(test_x2)  # content

        # 為數字序列加入 zero padding

        x1_test = keras.preprocessing.sequence.pad_sequences(x1_test, maxlen=MAX_SEQUENCE_LENGTH1)
        x2_test = keras.preprocessing.sequence.pad_sequences(x2_test, maxlen=MAX_SEQUENCE_LENGTH2)

        # 利用已訓練的模型做預測
        predictions = self.model.predict([x1_test, x2_test])
        print(predictions)
        m1 = predictions[0][0]
        m2 = predictions[0][1]
        m3 = predictions[0][2]

        ina = max(m1, m2, m3)
        if ina == m1:
            return "green"
        elif ina == m2:
            return "blue"
        else:
            return "red"