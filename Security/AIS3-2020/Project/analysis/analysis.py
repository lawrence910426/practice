import jieba
import pandas
import logging
import numpy as np
from gensim.models import word2vec
import csv

def preprocess(data_set, model_name):
    corpus = []
    for file_name in data_set:
        with open("words/" + file_name, newline='') as csvfile:
            for row in csvfile:
                corpus.append(row)
        
    jieba_sliced = [jieba.cut(item, cut_all=False) for item in corpus]
    metadata = []
    for sentence in jieba_sliced:
        metadata.append([word for word in sentence])
    print(metadata)

    logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)
    model = word2vec.Word2Vec(metadata, size=50, workers=4, iter=30)
    model.save(model_name)

def query(model, queries):
    return [model.wv.most_similar(item) for item in queries]

def train():
    preprocess(["Blue_1.csv"], "Blue.model")
    preprocess(["Green_1.csv"], "Green.model")
    preprocess(["Red_1.csv"], "Red.model")

def question():
    questions = ['人民', '疫情', '新冠', '肺炎']
    model = {
        "Green": word2vec.Word2Vec.load('Green.model'),
        "Blue": word2vec.Word2Vec.load('Blue.model'),
        "Red": word2vec.Word2Vec.load('Red.model')
    }
    for item in questions:
        print("=======================")
        print(item)
        print(pandas.DataFrame(query(model["Blue"], [item])[0]))
        print(pandas.DataFrame(query(model["Green"], [item])[0]))
        print(pandas.DataFrame(query(model["Red"], [item])[0]))
        print("=======================")

# train()
question()