.data
	a: .asciz "a" #CHAR:"a" HEX:"61" DEC:"97"
	b: .asciz "b" #CHAR:"b" HEX:"62" DEC:"98"
	c: .asciz "c" #CHAR:"c" HEX:"63" DEC:"99"
	d: .asciz "d" #CHAR:"d" HEX:"64" DEC:"100"
	e: .asciz "e" #CHAR:"e" HEX:"65" DEC:"101"
	f: .asciz "f" #CHAR:"f" HEX:"66" DEC:"102"
	g: .asciz "g" #CHAR:"g" HEX:"67" DEC:"103"
	h: .asciz "h" #CHAR:"h" HEX:"68" DEC:"104"
	i: .asciz "i" #CHAR:"i" HEX:"69" DEC:"105"
	j: .asciz "j" #CHAR:"j" HEX:"6a" DEC:"106"
	k: .asciz "k" #CHAR:"k" HEX:"6b" DEC:"107"
	l: .asciz "l" #CHAR:"l" HEX:"6c" DEC:"108"
	m: .asciz "m" #CHAR:"m" HEX:"6d" DEC:"109"
	n: .asciz "n" #CHAR:"n" HEX:"6e" DEC:"110"
	o: .asciz "o" #CHAR:"o" HEX:"6f" DEC:"111"
	p: .asciz "p" #CHAR:"p" HEX:"70" DEC:"112"
	q: .asciz "q" #CHAR:"q" HEX:"71" DEC:"113"
	r: .asciz "r" #CHAR:"r" HEX:"72" DEC:"114"
	s: .asciz "s" #CHAR:"s" HEX:"73" DEC:"115"
	t: .asciz "t" #CHAR:"t" HEX:"74" DEC:"116"
	u: .asciz "u" #CHAR:"u" HEX:"75" DEC:"117"
	v: .asciz "v" #CHAR:"v" HEX:"76" DEC:"118"
	w: .asciz "w" #CHAR:"w" HEX:"77" DEC:"119"
	x: .asciz "x" #CHAR:"x" HEX:"78" DEC:"120"
	y: .asciz "y" #CHAR:"y" HEX:"79" DEC:"121"
	z: .asciz "z" #CHAR:"z" HEX:"7a" DEC:"122"
	miden: .asciz "0" #CHAR:"0" HEX:"30" DEC:"48"
	one: .asciz "1" #CHAR:"1" HEX:"31" DEC:"49"
	two: .asciz "2" #CHAR:"2" HEX:"32" DEC:"50"
	three: .asciz "3" #CHAR:"3" HEX:"33" DEC:"51"
	four: .asciz "4" #CHAR:"4" HEX:"34" DEC:"52"
	five: .asciz "5" #CHAR:"5" HEX:"35" DEC:"53"
	six: .asciz "6" #CHAR:"6" HEX:"36" DEC:"54"
	seven: .asciz "7" #CHAR:"7" HEX:"37" DEC:"55"
	eight: .asciz "8" #CHAR:"8" HEX:"38" DEC:"56"
	nine: .asciz "9" #CHAR:"9" HEX:"39" DEC:"57:

	str: .asciz "xyz"
	#xyz in little-endian is "8026488" because the string in hex is "007a7978" (\0-z-x-y)
	#xyz in big-endian is "2021227008" because the string in hex is "78797a00" (x-y-z-\0)

.text
main:
	lw x10,str
	addi x17,x0,1
	ecally
