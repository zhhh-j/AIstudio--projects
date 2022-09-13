import numpy as np

text = "you say goodbye and I say hello."

def preprocess(text):
    '''
    对文本数据简单预处理
    '''
    text = text.lower()
    text = text.replace(".", " .")
    words = text.split(" ")
    word_to_id = {}
    id_to_word = {}
    for word in words:
        if word not in word_to_id:
            new_id = len(word_to_id)
            word_to_id[word] = new_id
            id_to_word[new_id] = word

    corpus = np.array([word_to_id[w] for w in words])

    return corpus, word_to_id, id_to_word
