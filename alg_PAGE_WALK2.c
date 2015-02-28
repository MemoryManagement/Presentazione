
unsigned long int get_cr3()
{
	unsigned long int CR3;
	__asm__ __volatile__ (
        "mov %%cr3, %%rax\n"
        "mov %%rax, %0\n"
    :   "=m" (CR3)
    :
    :   "%rax"
    );
    return CR3;
}

unsigned long int shift_dx (int destra, int sinistra, unsigned long int addr)
{
	addr = addr>>destra;
	addr = addr<<sinistra;
	return addr;
}

unsigned long int shift_sx (int sinistra, int destra, unsigned long int addr)
{
	addr = addr<<sinistra;
	addr = addr>>destra;
	return addr;
}

unsigned long int remove_flags (unsigned long int addr)
{
	addr = shift_dx(12, 12, addr);
	addr = shift_sx(16, 16, addr);
	return addr;
}

unsigned long int passo (unsigned long int sup, unsigned long int index)
{
	unsigned long int inf;
	inf = sup[index];
	inf = remove_flags(inf);
	return PAGE_OFFSET + inf;
}

unsigned long int page_walk (addr, pgd)
{
	//dichiarazione variabili

	//calcolo degli indici
	pgd_index = shift_sx(16, 55, addr);
	pud_index = shift_sx(25, 55, addr);
	pmd_index = shift_sx(34, 55, addr);
	pte_index = shift_sx(43, 55, addr);
	offset = shift_sx(52, 52, addr);

	//page_walk
	pud = passo (pgd, pgd_index);
	pmd = passo (pud, pud_index);
	pte = passo (pmd, pmd_index);
	page = passo (pmd, pmd_index);

	//aggiungo l'offset
	word = page + offset;
	return word;
}
