.name "jocko"
.comment "primate"

sti r1, %:live, %1
sti r1, %:cool, %1
lfork %2000
ld %0, r2
live:
	live %0
cool:
	trap %0
   ld  %190317059, r2
   ld %500, r3
   xor r4, r4, r4
   zjmp %17
   ld %151120384, r2
   ld %506, r3
   xor r4, r4, r4
   sti r2, r3, %0
   zjmp %490
