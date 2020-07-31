import pandas as pd
import jieba_fast.posseg as pseg
import keras
import numpy as np
from sklearn.model_selection import train_test_split
from keras import layers
from keras.utils import plot_model
# 建立孿生 LSTM 架構（Siamese LSTM）
from keras import Input
from keras.layers import Embedding,LSTM, concatenate, Dense
from keras.models import Model

train = pd.read_csv(r"/Users/armin/Desktop/AIS3專題/total.csv", encoding='utf-8')
train["title"] = train["title"].astype(str)
train["content"] = train["content"].astype(str)
cols = ['title', 'content', 'label']
train = train.loc[:, cols]

index = 0

def jieba_tokenizer(text):
    words = pseg.cut(text)
    return ' '.join([word for word, flag in words if flag != 'x'])

train['title_tokenized'] = train.loc[:, 'title'].apply(jieba_tokenizer)
train['content_tokenized'] = train.loc[:, 'content'].apply(jieba_tokenizer)

MAX_NUM_WORDS = 5000 #最高不超過 5000 個詞彙
tokenizer = keras.preprocessing.text.Tokenizer(num_words=MAX_NUM_WORDS)

#合併-----------------------------------------
corpus_x1 = train.title_tokenized
corpus_x2 = train.content_tokenized
corpus = pd.concat([corpus_x1, corpus_x2])

tokenizer.fit_on_texts(corpus)
x1_train = tokenizer.texts_to_sequences(corpus_x1)  #title
x2_train = tokenizer.texts_to_sequences(corpus_x2)  #content

MAX_SEQUENCE_LENGTH = 5000  #設置最大長度為20，不足補零
x1_train = keras.preprocessing .sequence .pad_sequences(x1_train,maxlen=MAX_SEQUENCE_LENGTH) #title
x2_train = keras.preprocessing.sequence .pad_sequences(x2_train,maxlen=MAX_SEQUENCE_LENGTH)  #content

label_to_index = {'green': 0, 'blue': 1, 'red': 2,'other':3}    #進行label轉換
y_train = train.label.apply(lambda x: label_to_index[x])
y_train = np.asarray(y_train) .astype('float32')
#print(y_train[:3])

#OneHotEncoing
y_train = keras .utils.to_categorical(y_train)
#print(y_train[:3])


#測試集切割－訓練、驗證、測試
VALIDATION_RATIO = 0.1
RANDOM_STATE = 9527
title_train, title_val, content_train, content_val, y_train, y_val = train_test_split(x1_train, x2_train, y_train, test_size=VALIDATION_RATIO, random_state=RANDOM_STATE)

#實際運行
# 基本參數設置，有幾個分類 (需要按照實際輸入樣本有的去設置，不然會出錯)
NUM_CLASSES = 3

# 在語料庫裡有多少詞彙
MAX_NUM_WORDS = 5000

# 一個標題最長有幾個詞彙
MAX_SEQUENCE_LENGTH = 5000

# 一個詞向量的維度
NUM_EMBEDDING_DIM = 256

# LSTM 輸出的向量維度
NUM_LSTM_UNITS = 128

embedding_layer = layers.Embedding(MAX_NUM_WORDS,NUM_EMBEDDING_DIM)

# 分別定義 title & content 為模型輸入
# 兩個都是一個長度為 5000 的數字序列 暫定
top_input = Input(shape=(MAX_SEQUENCE_LENGTH, ),dtype='int32')
bm_input = Input(shape=(MAX_SEQUENCE_LENGTH, ),dtype='int32')

# 詞嵌入層
# 經過詞嵌入層的轉換，title & content 都變成
# 一個詞向量的序列，而每個詞向量的維度為 256
embedding_layer = Embedding(MAX_NUM_WORDS, NUM_EMBEDDING_DIM)
top_embedded = embedding_layer(top_input)
bm_embedded = embedding_layer(bm_input)

# LSTM 層，title & content 經過此層後，為一個 128 維度向量
shared_lstm = LSTM(NUM_LSTM_UNITS)
top_output = shared_lstm(top_embedded)
bm_output = shared_lstm(bm_embedded)

# 串接層將title & content 的結果串接單一向量，方便跟全連結層相連
merged = concatenate([top_output, bm_output], axis=-1)

# 全連接層搭配 Softmax Activation，可以回傳 4 個類別，屬於各類別的可能機率
dense = Dense(units=NUM_CLASSES, activation='softmax')
predictions = dense(merged)

# 我們的模型就是將數字序列的輸入，轉換成 3 個分類的機率的所有步驟 / 層的總和
model = Model(inputs=[top_input, bm_input],outputs=predictions)

model.compile(optimizer='rmsprop',loss='categorical_crossentropy',metrics=['accuracy'])

# 決定一次要放多少成對標題給模型訓練
BATCH_SIZE = 50

# 決定模型要看整個訓練資料集幾遍
NUM_EPOCHS = 5

# 實際訓練模型
history = model.fit(x=[title_train,content_train],y=y_train,batch_size=BATCH_SIZE,epochs=NUM_EPOCHS,validation_data=([title_val, content_val],y_val),shuffle=True)

model.save('my_model.h5')   # HDF5 file, you have to pip3 install h5py if don't have it
del model  # deletes the existing model