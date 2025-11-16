IN=main.c
OUT=app
CFLAGS+='-Wall'
CFLAGS+='-Wextra'

.PHONY: $(OUT) clean

$(OUT):
	cc $(CFLAGS) $(IN) -o $(OUT)

run:
	./$(OUT)

clean:
	rm -rf $(OUT)
