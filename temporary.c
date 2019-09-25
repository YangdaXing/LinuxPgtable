#include <stdio.h>

int main()
{
    printf("Hello world\n");
    return 0;
}
static inline pte_t *pte_offset_kernel(pmd_t *pmd, unsigned long address)
{
    ktime_t now;
    s64 delta;
    now = ktime_get();
    delta = ktime_to_ns(now);
    printk("The time is %lld ,the running process's pid is %d ",delta,current->pid);
	return (pte_t *)pmd_page_vaddr(*pmd) + pte_index(address);
}
