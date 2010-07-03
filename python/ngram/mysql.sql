-- ngram作成
create table ngram(id int primary key auto_increment, context text binary not null, word text not null, freq int not null, total int not null, prob double not null);
load data infile "/home/nokuno/data/linux/ngram/1gram_prob.txt" into table ngram fields terminated by " " escaped by '' (word, freq, total, prob);
load data infile "/home/nokuno/data/linux/ngram/2gram_prob.txt" into table ngram fields terminated by "\t" escaped by '' (context, word, freq, total, prob);
load data infile "/home/nokuno/data/linux/ngram/3gram_prob.txt" into table ngram fields terminated by "\t" escaped by '' (context, word, freq, total, prob);
load data infile "/home/nokuno/data/linux/ngram/4gram.txt" into table ngram fields terminated by "\t" escaped by '' (context, word, freq, total, prob);
load data infile "/home/nokuno/data/linux/ngram/5gram.txt" into table ngram fields terminated by "\t" escaped by '' (context, word, freq, total, prob);
create index index1 on ngram(context(255), prob);

