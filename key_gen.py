def find_generators(prime):
    ret=[]
    for g in range(1,prime):
        is_generated=[False for _ in range(prime)]
        is_found=0
        for m in range(1, prime):
            is_generated[(g**m)%prime]=True
        for b in is_generated[1:prime]:
            is_found+=1if b else 0
        if is_found == prime-1:
            ret.append(g)
    return ret
