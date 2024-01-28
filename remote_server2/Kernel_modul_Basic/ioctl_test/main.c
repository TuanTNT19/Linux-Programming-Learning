#include <linux/module.h>  /* Thu vien nay dinh nghia cac macro nhu module_init/module_exit */
#include <linux/fs.h>      /* Thu vien nay dinh nghia cac ham allocate major/minor number */
#include <linux/device.h>  /* Thu vien nay dinh nghia cac ham class_create/device_create */
#include <linux/cdev.h>    /* Thu vien nay dinh nghia cac ham kmalloc */
#include<linux/slab.h>     /* Thu vien nay dinh nghia cac ham cdev_init/cdev_add */
#include<linux/uaccess.h>  /* Thu vien nay dinh nghia cac ham copy_to_user/copy_from_user *//* Thu vien nay dinh nghia cac ham cdev_init/cdev_add */
#include <linux/ioctl.h>  // This header contains the necessary definitions for __IOW


#define DRIVER_AUTHOR "TuanTNT xxxxxxxx@gmail.com"
#define DRIVER_DESC   "Hello world kernel module"

#define ON _IOW('a', '1', int)
#define OFF _IOW('a', '0', int)


typedef struct {
    dev_t dev_num;
    struct class *m_class;
    struct cdev m_cdev;
    int size;
    //char *k_buff;
} m_foo_dev;

char kernel_buff[40];

m_foo_dev mdev;

static long ioctl_ex(struct file *file, unsigned int cmd, unsigned long arg);

static struct file_operations fops =
{
    .owner      = THIS_MODULE,
    .unlocked_ioctl = ioctl_ex,
};

static long ioctl_ex(struct file *file, unsigned int cmd, unsigned long arg)
{
         switch(cmd) {
                case ON:
                        pr_info("ON feature\n");
                        break;
                case OFF:
                       pr_info("OFF feature\n");
                        break;
                default:
                        pr_info("Default\n");
                        break;
        }
        return 0;
}





static int __init Khoitao(void)
{
    if (alloc_chrdev_region(&mdev.dev_num, 0, 1, "my-cdev"))
    {
        pr_err("ERROR: Can not make number device\n");
        return -1;
    }
    pr_info("Hello from main\n");
    
    pr_info("Major : %d    Minor : %d\n", MAJOR(mdev.dev_num), MINOR(mdev.dev_num));
    
    if ((mdev.m_class = class_create(THIS_MODULE, "my_class")) == NULL){
        pr_err("ERROR: Can not create class\n");
        goto rm_dev_num;
    }

    if (device_create(mdev.m_class, NULL, mdev.dev_num, NULL, "my_device") == NULL)
    {
        pr_err("ERROR: Can not create device\n");
        goto rm_class;

    }

    cdev_init(&mdev.m_cdev, &fops);
    if (cdev_add(&mdev.m_cdev, mdev.dev_num, 1) < 0)
    {
        pr_err("ERROR: Can not add device\n");
        goto rm_dev_num;
    }

    return 0;


rm_dev_num:
    unregister_chrdev_region(mdev.dev_num,1);
rm_class:
    class_destroy(mdev.m_class);

    return -1;
}

static void __exit Huy(void)
{
    device_destroy(mdev.m_class, mdev.dev_num);
    class_destroy(mdev.m_class);
    cdev_del(&mdev.m_cdev);  
    unregister_chrdev_region(mdev.dev_num,1);

    pr_info("GOODBYE from main\n");

}


module_init(Khoitao);
module_exit(Huy);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);  
