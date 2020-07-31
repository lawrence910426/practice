import jieba
#　from gensim.test.utils import common_texts, get_tmpfile
import pandas
import logging
import numpy as np
from gensim.models import word2vec
import csv

def preprocess(data_set, model_name):
    corpus = []
    with open(data_set, newline='') as csvfile:
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
    model = word2vec.Word2Vec.load(model)
    return [model.wv.most_similar(item) for item in queries]

# preprocess('people.csv', 'people.model')
questions = ['人民', '疫情', '新冠']
for item in questions:
    print("=======================")
    print(item)
    print(pandas.DataFrame(query('people.model', [item])[0]))
    print("=======================")