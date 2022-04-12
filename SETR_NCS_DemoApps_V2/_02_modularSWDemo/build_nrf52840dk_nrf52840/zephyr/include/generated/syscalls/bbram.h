
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef Z_INCLUDE_SYSCALLS_BBRAM_H
#define Z_INCLUDE_SYSCALLS_BBRAM_H


#ifndef _ASMLANGUAGE

#include <syscall_list.h>
#include <syscall.h>

#include <linker/sections.h>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic push
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#if !defined(__XCC__)
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern int z_impl_bbram_check_invalid(const struct device * dev);

__pinned_func
static inline int bbram_check_invalid(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_BBRAM_CHECK_INVALID);
	}
#endif
	compiler_barrier();
	return z_impl_bbram_check_invalid(dev);
}


extern int z_impl_bbram_check_standby_power(const struct device * dev);

__pinned_func
static inline int bbram_check_standby_power(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_BBRAM_CHECK_STANDBY_POWER);
	}
#endif
	compiler_barrier();
	return z_impl_bbram_check_standby_power(dev);
}


extern int z_impl_bbram_check_power(const struct device * dev);

__pinned_func
static inline int bbram_check_power(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_BBRAM_CHECK_POWER);
	}
#endif
	compiler_barrier();
	return z_impl_bbram_check_power(dev);
}


extern int z_impl_bbram_get_size(const struct device * dev, size_t * size);

__pinned_func
static inline int bbram_get_size(const struct device * dev, size_t * size)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&dev, *(uintptr_t *)&size, K_SYSCALL_BBRAM_GET_SIZE);
	}
#endif
	compiler_barrier();
	return z_impl_bbram_get_size(dev, size);
}


extern int z_impl_bbram_read(const struct device * dev, size_t offset, size_t size, uint8_t * data);

__pinned_func
static inline int bbram_read(const struct device * dev, size_t offset, size_t size, uint8_t * data)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke4(*(uintptr_t *)&dev, *(uintptr_t *)&offset, *(uintptr_t *)&size, *(uintptr_t *)&data, K_SYSCALL_BBRAM_READ);
	}
#endif
	compiler_barrier();
	return z_impl_bbram_read(dev, offset, size, data);
}


extern int z_impl_bbram_write(const struct device * dev, size_t offset, size_t size, const uint8_t * data);

__pinned_func
static inline int bbram_write(const struct device * dev, size_t offset, size_t size, const uint8_t * data)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke4(*(uintptr_t *)&dev, *(uintptr_t *)&offset, *(uintptr_t *)&size, *(uintptr_t *)&data, K_SYSCALL_BBRAM_WRITE);
	}
#endif
	compiler_barrier();
	return z_impl_bbram_write(dev, offset, size, data);
}


#ifdef __cplusplus
}
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif

#endif
#endif /* include guard */
