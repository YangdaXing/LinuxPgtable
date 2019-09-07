#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/thread_info.h>
 
//定义要Hook的函数，本例中_do_fork
static struct kprobe kp =
{
    .symbol_name = "_do_fork",
};
 
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    printk(KERN_ERR "hook in handler_pre");
    return 0;
}
 
static void handler_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
 
    printk(KERN_ERR "hook in handler_post");
}
 
static int handler_fault(struct kprobe *p, struct pt_regs *regs, int trapnr)
{
    printk(KERN_ERR "hook in handler_fault");
    return 0;
}
 
 
static int __init kprobe_init(void)
{
    int ret;
    kp.pre_handler = handler_pre;
    kp.post_handler = handler_post;
    kp.fault_handler = handler_fault;
 
    ret = register_kprobe(&kp);
    if (ret < 0)
    {
        printk(KERN_INFO "register_kprobe failed, returned %d\n", ret);
        return ret;
    }
    printk(KERN_INFO "Planted kprobe at %p\n", kp.addr);
    return 0;
}
 
static void __exit kprobe_exit(void)
{
    unregister_kprobe(&kp);
    printk(KERN_INFO "kprobe at %p unregistered\n", kp.addr);
}
 
module_init(kprobe_init)
module_exit(kprobe_exit)
MODULE_LICENSE("GPL"); 

