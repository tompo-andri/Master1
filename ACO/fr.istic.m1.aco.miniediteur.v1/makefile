# Makefile

# Dir variables
BINDIR=./bin
SRCDIR=./src
TESTDIR=./tests
DOCDIR=./doc

# Librairies and compilation options
JUNITDIR=$(HOME)/Librairies/junit-4.12.jar:$(HOME)/Librairies/hamcrest-core-1.3.jar:$(HOME)/Librairies/mockito-all-1.9.5.jar
JUNIT_CMD=java -cp $(BINDIR):$(JUNITDIR) org.junit.runner.JUnitCore
JAVA_CMD=java -cp $(BINDIR):$(JUNITDIR)
JAVAC_CMD=javac -cp $(BINDIR):$(JUNITDIR) -d $(BINDIR)
JAVADOC_CMD=javadoc -classpath $(BINDIR):$(JUNITDIR)
JAVADOC_OPTIONS=-d $(DOCDIR)
JAR_CMD=jar cvfm
JAR_NAME=EditeurV1.jar
MANIFEST_FILE=META-INF/MANIFEST.MF

# The packages
COMMAND=command
INVOKER=invoker
RECEIVER=receiver
CLIENT=client
TESTS=tests


# Default compilation
all: $(RECEIVER) ihm_interface $(COMMAND) $(INVOKER) $(CLIENT)


# Packages compilation
$(RECEIVER): $(SRCDIR)/$(RECEIVER)/SelectionInterface.java $(SRCDIR)/$(RECEIVER)/Selection.java $(SRCDIR)/$(RECEIVER)/BufferInterface.java $(SRCDIR)/$(RECEIVER)/Buffer.java $(SRCDIR)/$(RECEIVER)/MoteurEditeurInterface.java $(SRCDIR)/$(RECEIVER)/MoteurEditeur.java $(SRCDIR)/$(RECEIVER)/PressePapierInterface.java $(SRCDIR)/$(RECEIVER)/PressePapier.java
	$(JAVAC_CMD) $(SRCDIR)/$(RECEIVER)/*.java

ihm_interface: $(SRCDIR)/$(INVOKER)/IhmInterface.java
	$(JAVAC_CMD) $(SRCDIR)/$(INVOKER)/IhmInterface.java

$(COMMAND): $(SRCDIR)/$(COMMAND)/CommandeInterface.java $(SRCDIR)/$(COMMAND)/Saisir.java $(SRCDIR)/$(COMMAND)/Selectionner.java $(SRCDIR)/$(COMMAND)/Copier.java $(SRCDIR)/$(COMMAND)/Coller.java $(SRCDIR)/$(COMMAND)/Couper.java
	$(JAVAC_CMD) $(SRCDIR)/$(COMMAND)/*.java

$(INVOKER): $(SRCDIR)/$(INVOKER)/IhmInterface.java $(SRCDIR)/$(INVOKER)/MyIhm.java
	$(JAVAC_CMD) $(SRCDIR)/$(INVOKER)/*.java

$(CLIENT): $(SRCDIR)/$(CLIENT)/Editeur.java
	$(JAVAC_CMD) $(SRCDIR)/$(CLIENT)/*.java


# Tests compilation
$(TESTS): $(RECEIVER)test $(COMMAND)test

# Packages tests compilation
$(RECEIVER)test: $(TESTDIR)/$(RECEIVER)/TestSelection.java $(TESTDIR)/$(RECEIVER)/TestBuffer.java $(TESTDIR)/$(RECEIVER)/TestPressePapier.java $(TESTDIR)/$(RECEIVER)/TestMoteurEditeur.java
	$(JAVAC_CMD) $(TESTDIR)/$(RECEIVER)/*.java

$(COMMAND)test: $(TESTDIR)/$(COMMAND)/TestCopier.java $(TESTDIR)/$(COMMAND)/TestColler.java $(TESTDIR)/$(COMMAND)/TestCouper.java $(TESTDIR)/$(COMMAND)/TestSelectionner.java $(TESTDIR)/$(COMMAND)/TestSaisir.java
	$(JAVAC_CMD) $(TESTDIR)/$(COMMAND)/*.java


# Whole Junit tests
junit: $(TESTS) junit_$(RECEIVER)test junit_$(COMMAND)test

# Packages tests
junit_$(RECEIVER)test:
	$(JUNIT_CMD) $(RECEIVER).TestSelection $(RECEIVER).TestBuffer $(RECEIVER).TestPressePapier $(RECEIVER).TestMoteurEditeur

junit_$(COMMAND)test:
	$(JUNIT_CMD) $(COMMAND).TestCopier $(COMMAND).TestColler $(COMMAND).TestCouper $(COMMAND).TestSaisir $(COMMAND).TestSelectionner


# Run the program
run:
	$(JAVA_CMD) $(CLIENT).Editeur


# Clean
clean:
	rm -rf $(BINDIR)/$(RECEIVER) $(BINDIR)/$(INVOKER) $(BINDIR)/$(COMMAND) $(BINDIR)/$(CLIENT) $(DOCDIR) $(JAR_NAME)


# The whole build and then tests
build: all junit


# Generate the javadoc
javadoc:
	$(JAVADOC_CMD) $(SRCDIR)/$(CLIENT)/*.java $(SRCDIR)/$(RECEIVER)/*.java $(SRCDIR)/$(INVOKER)/*.java $(SRCDIR)/$(COMMAND)/*.java $(JAVADOC_OPTIONS)


# Generate the jar executable file
jar: all
	$(JAR_CMD) $(JAR_NAME) $(MANIFEST_FILE) $(BINDIR)
