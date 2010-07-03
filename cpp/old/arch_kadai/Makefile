TARGET = gmbp
OBJS = main.o util.o data.o solve.o
SAMPLE = hello

CC = icc
CFLAGS = -O2 -w1
LDFLAGS = -s
LIBS = -lmpi

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

$(SAMPLE): %: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	- rm -f $(TARGET) $(OBJS) $(SAMPLE)

$(OBJS): gmbp.h
