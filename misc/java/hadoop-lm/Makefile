all:
	javac -classpath ${HADOOP}/hadoop-core.jar:${HADOOP}/lib/commons-cli-1.2.jar *.java -Xlint:unchecked
	jar cvfe ngram-count.jar NgramCount *.class
	rm *.class
