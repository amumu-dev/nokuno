create table unigram(id int primary key auto_increment, word text not null, freq int not null);
load data infile "/home/nokuno/data/wikipedia/ngram/unigram.txt" into table unigram fields terminated by "\t" escaped by '' (word,freq);
create index word_index on unigram(word(255));

