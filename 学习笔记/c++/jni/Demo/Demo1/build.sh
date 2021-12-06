# 编译java
# 如果有额外的jar包需要使用 javac -cp ....
javac *.java
# 编译C++ 
# 注意JAVA_HOME JRE_HOME 与 LD_LIBRARY_PATH的配置
# export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64
# 一些高等级的java jdk和jre可能已经合并成一个文件夹了
# export JRE_HOME = JAVA_HOME or ${JAVA_HOME}/jre  
# export LD_LIBRARY_PATH=${JRE_HOME}/lib/server
g++ -o testjava TestJNI.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/server -ljvm 
