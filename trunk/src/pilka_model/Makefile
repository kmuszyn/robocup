
# Desc: Sample make file for Gazebo plugin
# CVS: $Id: Makefile.example,v 1.4 2004/11/04 07:29:58 inspectorg Exp $

all: ball.so


%.o: %.cc
	$(CXX) -Wall -g3 `pkg-config --cflags gazebo` -c $<

%.so: %.o
	$(CXX) -shared -nostartfiles -o $@ $< #libbodies.a

clean:
	rm -f *.o *.so
