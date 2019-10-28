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
    printk("pte_offset_kernel is running!\nThe time is %lld ,the running process's pid is %d ",delta,current->pid);
	return (pte_t *)pmd_page_vaddr(*pmd) + pte_index(address);
}

static inline unsigned int pgd_index(unsigned long address)
{
    ktime_t now;
    s64 delta;
    now = ktime_get();
    delta = ktime_to_ns(now);
    printk("pgd_index function is running\n,The time is %lld ,the running process's pid is %d ",delta,current->pid);
	return (((address) >> PGDIR_SHIFT) & (PTRS_PER_PGD - 1));

}

static inline pud_t *pud_offset(p4d_t *p4d, unsigned long address)
{
	return (pud_t *)p4d_page_vaddr(*p4d) + pud_index(address);
}

#include <linux/timekeeping.h>//ktime_get()
#include <linux/sched.h>
#include <linux/kernel.h>     //printk()

