#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>
#include<linux/gfp.h>

struct jprobe alloc_jp;


int jp_do_alloc(gfp_t gfp_mask, unsigned int order)
{
    if(current)   
        printk("%s %d",current->comm,order);
    else
        printk("%d",order);
    jprobe_return();
    return 0;
}


static __init int jprobes_alloc_init(void)
{    
    alloc_jp.kp.symbol_name = "alloc_pages";

    alloc_jp.entry = JPROBE_ENTRY(jp_do_alloc);


    register_jprobe(&alloc_jp);
    
    return 0;
}



static __exit void jprobes_alloc_cleanup(void)
{
    unregister_jprobe(&alloc_jp);
}

module_init(jprobes_alloc_init); 
module_exit(jprobes_alloc_cleanup);
MODULE_LICENSE("GPL");
