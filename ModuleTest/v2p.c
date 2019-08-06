#include <linux/init.h>//包含了模块的初始化的宏定义及一些其他函数的初始化函数
#include <linux/module.h>//内核模块必备头文件
#include <linux/mm.h>//// 内存管理相关头文件，含有页面大小定义和一些页面释放函数原型。
#include <linux/mm_types.h>//内存管理相关头文件
#include <linux/sched.h>//进程调度相关头文件
#include <linux/export.h>//必要的头文件
#include <linux/delay.h>//延时函数头文件
//定义全局变量
static unsigned long cr0,cr3;//定义CR0和CR3

static unsigned long vaddr = 0;//定义虚拟地址的全局变量

pgd_t *pgd;
p4d_t *p4d;    
pud_t *pud;
pmd_t *pmd;
pte_t *pte;


static void get_pgtable_macro(void)
{
  cr0 = read_cr0();//获得CR0寄存器的值
  cr3 = read_cr3_pa();//获得CR3寄存器的值
  printk("cr0 = 0x%lx, cr3 = 0x%lx\n",cr0,cr3);//打印CR0和CR3的值
  //_SHIFT宏用来描述线性地址中相应字段所能映射区域大小的位数
  printk("BITS_PER_LONG = %d\n",BITS_PER_LONG);
  printk("PGDIR_SHIFT = %d\n", PGDIR_SHIFT);//打印页全局目录项能映射的区域大小的位数
  printk("P4D_SHIFT = %d\n",P4D_SHIFT);//打印P4D目录项能映射的区域大小的位数
  printk("PUD_SHIFT = %d\n", PUD_SHIFT);//打印页上级目录项能映射的区域大小的位数
  printk("PMD_SHIFT = %d\n", PMD_SHIFT);//打印页中间目录项可以映射的区域大小的位数
  printk("PAGE_SHIFT = %d\n", PAGE_SHIFT);//打印page_offset字段所能映射区域大小的位数
  //指示相应页目录表中项的个数
  printk("PTRS_PER_PGD = %d\n", PTRS_PER_PGD);//打印页全局目录项数
  printk("PTRS_PER_P4D = %d\n", PTRS_PER_P4D);//打印P4D目录项数
  printk("PTRS_PER_PUD = %d\n", PTRS_PER_PUD);//打印页上级目录项数
  printk("PTRS_PER_PMD = %d\n", PTRS_PER_PMD);//打印页中级目录项数
  printk("PTRS_PER_PTE = %d\n", PTRS_PER_PTE);//打印页表项数
  printk("PAGE_MASK = 0x%lx\n", PAGE_MASK);//页内偏移掩码，屏蔽page_offset字段
}

static unsigned long pud_table(unsigned long vaddr)
{
    // 尝试打印内核页表的内容 
     pud_t *pud_tmp;
     unsigned long vaddr_t = 0;
     unsigned long vaddr_tmp = 0;

     unsigned long i;
     printk("The pud_table is in the follow list \n"); 
     vaddr_t = vaddr & 0xffffff803fffffff;//手动将PUD位清零  
     printk("vaddr_t = %lx\n",vaddr_t); 
     for(i=0;i<512;i++) 
     { 
         vaddr_tmp = vaddr_t |(i<<30); 
         printk("vaddr_tmp_%lx = %lx",i,vaddr_tmp); 
            //获取页上级目录PUD */
         pud_tmp = pud_offset(p4d, vaddr_tmp);//获得pud的地址 
         printk("pud_val_%lu = 0x%lx, pud_index_%lu = %lu\n", i,pud_val(*pud_tmp),i,pud_index(vaddr_tmp));//打印pud地址和索引 */
         if (pud_none(*pud_tmp)) //判断pud页表项是否为空 
         { 
             printk("not mapped in pud\n"); 
             continue;
         } 
      }
     return vaddr;
}

static unsigned long pmd_table(unsigned long vaddr)
{
    // 尝试打印内核页表的内容 
     pmd_t *pmd_tmp;
     unsigned long vaddr_t = 0;
     unsigned long vaddr_tmp = 0;

     unsigned long i;
     printk("The pmd_table is in the follow list \n"); 
     vaddr_t = vaddr & 0xffffffffc01fffff;//手动将pmd位清零  
     printk("vaddr_t = %lx\n",vaddr_t); 
     for(i=0;i<512;i++) 
     { 
         vaddr_tmp = vaddr_t |(i<<21); 
         printk("vaddr_tmp_%lx = %lx",i,vaddr_tmp); 
            //获取页上级目录pmd */
         pmd_tmp = pmd_offset(pud, vaddr_tmp);//获得pmd的地址 
         printk("pmd_val_%lu = 0x%lx, pmd_index_%lu = %lu\n", i,pmd_val(*pmd_tmp),i,pmd_index(vaddr_tmp));//打印pud地址和索引 */
         if (pmd_none(*pmd_tmp)) //判断pmd页表项是否为空 
         { 
             printk("not mapped in pmd\n"); 
             continue;
         } 
      }
     return vaddr;
}

static unsigned long pte_table(unsigned long vaddr)
{
    // 尝试打印内核页表的内容 
     pte_t *pte_tmp;
     unsigned long vaddr_t = 0;
     unsigned long vaddr_tmp = 0;

     unsigned long i;
     printk("The pte_table is in the follow list \n"); 
     vaddr_t = vaddr & 0xffffffffffe00fff;//手动将pte位清零  
     printk("vaddr_t = %lx\n",vaddr_t); 
     for(i=0;i<512;i++) 
     { 
         vaddr_tmp = vaddr_t |(i<<12); 
         printk("vaddr_tmp_%lx = %lx",i,vaddr_tmp); 
            //获取页上级目录pte */
         pte_tmp = pte_offset_kernel(pmd, vaddr_tmp);//获得pte的地址 
         printk("pte_val_%lu = 0x%lx, pte_index_%lu = %lu\n", i,pte_val(*pte_tmp),i,pte_index(vaddr_tmp));//打印pud地址和索引 */
         if (pte_none(*pte_tmp)) //判断pte页表项是否为空 
         { 
             printk("not mapped in pte\n"); 
             continue;
         } 
      }
     return vaddr;
}


static unsigned long vaddr2paddr(unsigned long vaddr)
{
    //创建变量保存页目录项
    unsigned long paddr = 0;
    unsigned long page_addr = 0;
    unsigned long page_offset = 0;
    //获取页全局目录PGD，第一个参数当前进程的mm_struct，所有进程共享一个内核页表
    pgd = pgd_offset(current->mm,vaddr);//获得pgd的地址
    printk("pgd_val = 0x%lx, pgd_index = %lu\n", pgd_val(*pgd),pgd_index(vaddr));//打印pgd地址和索引
    if (pgd_none(*pgd))//判断pgd页表项是否为空
  {
        printk("not mapped in pgd\n");
        return -1;
    }
    //获取P4D，新的Intel芯片的MMU硬件规定可以进行5级页表管理，内核在PGD和PUD之间，增加了一个叫P4D的页目录
    p4d = p4d_offset(pgd, vaddr);//获得p4d的地址
    printk("p4d_val = 0x%lx, p4d_index = %lu\n", p4d_val(*p4d),p4d_index(vaddr));//打印p4d地址和索引
    if(p4d_none(*p4d))//判断p4d页表项是否为空
    {
        printk("not mapped in p4d\n");
        return -1;
    }
    //获取页上级目录PUD
    pud = pud_offset(p4d, vaddr);//获得pud的地址
    printk("pud_val = 0x%lx, pud_index = %lu\n", pud_val(*pud),pud_index(vaddr));//打印pud地址和索引
    if (pud_none(*pud)) //判断pud页表项是否为空
  {
        printk("not mapped in pud\n");
        return -1;
    }
    //获取页中间目录PMD
    pmd = pmd_offset(pud, vaddr);//获得pmd的地址
    printk("pmd_val = 0x%lx, pmd_index = %lu\n", pmd_val(*pmd),pmd_index(vaddr));//打印pmd地址和索引
    if (pmd_none(*pmd)) ////判断pmd页表项是否为空
  {
        printk("not mapped in pmd\n");
        return -1;
    }
    pte = pte_offset_kernel(pmd, vaddr);//获得pte的地址
    printk("pte_val = 0x%lx, ptd_index = %lu\n", pte_val(*pte),pte_index(vaddr));//打印pte地址和索引
    if (pte_none(*pte)) //判断pte页表项是否为空
  {
        printk("not mapped in pte\n");
        return -1;
    }
    page_addr = pte_val(*pte) & PAGE_MASK;//获得页框的物理地址
    page_offset = vaddr & ~PAGE_MASK;//获得页偏移地址
    paddr = page_addr | page_offset;//获得物理地址
    printk("page_addr = %lx, page_offset = %lu\n", page_addr, page_offset);
    printk("vaddr = %lx, paddr = %lx\n", vaddr, paddr);//打印虚拟地址和转换后的物理地址
    
    return paddr;
}

static int __init v2p_init(void)
{
    printk("vaddr to paddr module is running..\n");
    get_pgtable_macro();//打印主要参数
    printk("\n");
    vaddr = __get_free_page(GFP_KERNEL);//在内核ZONE_NORMAL中申请一块页面
    if (vaddr == 0)
    {
        printk("__get_free_page failed..\n");
        return 0;
    }
    sprintf((char *)vaddr, "hello world from kernel");
    printk("get_page_vaddr=0x%lx\n", vaddr);
    vaddr2paddr(vaddr);//调用线性地址转换物理地址的函数
    pud_table(vaddr); 
    pmd_table(vaddr); 
    pte_table(vaddr); 
    ssleep(600);//延时
    return 0;
}

static void __exit v2p_exit(void)
{
    printk("vaddr to paddr module is leaving..\n");
    free_page(vaddr);
}

module_init(v2p_init);//内核入口函数
module_exit(v2p_exit);//内核出口函数
MODULE_LICENSE("GPL"); //许可证
