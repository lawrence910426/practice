from keras.models import load_model
from tensorflow import keras
# 載入模型
def final_model(title, content):
    model = load_model('my_model.h5')

    tt = title
    aa = content
    #訓練
    test= [tt,aa]
    MAX_SEQUENCE_LENGTH = 5000

    MAX_NUM_WORDS = 5000 #最高不超過 5000 個詞彙
    tokenizer = keras.preprocessing.text.Tokenizer(num_words=MAX_NUM_WORDS)

    # 將詞彙序列轉為索引數字的序列
    x1_test = tokenizer.texts_to_sequences(test[0][0])
    x2_test = tokenizer.texts_to_sequences(test[0][1])

    # 為數字序列加入 zero padding
    x1_test = keras.preprocessing.sequence.pad_sequences(x1_test,maxlen=MAX_SEQUENCE_LENGTH)
    x2_test = keras.preprocessing.sequence.pad_sequences(x2_test,maxlen=MAX_SEQUENCE_LENGTH)

    # 利用已訓練的模型做預測
    predictions = model.predict([x1_test, x2_test])
    m1=predictions[0][0]
    m2=predictions[0][1]
    m3=predictions[0][2]

    ina = max(m1,m2,m3)
    if ina == m1:
        print("green")
        return {'answer': 'green'}
    elif ina == m2:
        print("blue")
        return {'answer': 'blue'}
    else:
        print("red")
        return {'answer' : 'red'}