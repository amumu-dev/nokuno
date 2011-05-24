all:
	javac -classpath ${HADOOP}/hadoop-core.jar:${HADOOP}/lib/commons-cli-1.2.jar *.java
	jar cvfe NgramCount.jar NgramCount *.class
	rm *.class
