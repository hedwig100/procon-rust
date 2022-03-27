DIR = src/bin/

a: 
	cargo run --bin a
b: 
	cargo run --bin b
c: 
	cargo run --bin c
d: 
	cargo run --bin d
e: 
	cargo run --bin e
f: 
	cargo run --bin f
g: 
	cargo run --bin g
h: 
	cargo run --bin h

setup:
	cp $(DIR)template.rs $(DIR)a.rs
	cp $(DIR)template.rs $(DIR)b.rs
	cp $(DIR)template.rs $(DIR)c.rs
	cp $(DIR)template.rs $(DIR)d.rs
	cp $(DIR)template.rs $(DIR)e.rs
	cp $(DIR)template.rs $(DIR)f.rs
	cp $(DIR)template.rs $(DIR)g.rs
	cp $(DIR)template.rs $(DIR)h.rs

clean:
	rm -f $(DIR)a.rs $(DIR)b.rs $(DIR)c.rs $(DIR)d.rs $(DIR)e.rs $(DIR)f.rs $(DIR)g.rs $(DIR)h.rs 

.PHONY: clean