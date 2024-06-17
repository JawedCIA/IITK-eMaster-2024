#include <types.h>
#include <mmap.h>
#include <fork.h>
#include <v2p.h>
#include <page.h>


#define PAGE_SIZE 4096
#define MASK 511
#define PTE_PFN_MASK 0xFFFFFFFFFF000
#define PTE_P 0x001
#define PTE_PRESENT 0x1
#define PTE_RW_BIT (1 << 3)


void flush_table() {
    u64 cr3; // Variable to store the value of CR3

    // Flush TLB by reloading CR3 register
       // Reload CR3 register
                       // No output operands
               // Input constraint: CR3 value stored in cr3
              // Clobber list: indicates memory may be affected

    asm volatile("mov %%cr3, %0; mov %0, %%cr3;" : "=r"(cr3) : : "memory");
}


// Retrieves the page table entry (PTE) corresponding to a given virtual address.
u64 *get_pte_entry(u64 cr3, u64 vaddr) {
     u64 *pgd_base = (u64 *)osmap(cr3);
    // Calculate indices for page table levels
     //Extracts the uppermost 9 bits of the virtual address after right-shifting it by 39 bits, which corresponds to the Page Global Directory (PGD) index.
     u64 pgd_index = (vaddr >> 39) & MASK;
     //Extracts the next 9 bits of the virtual address after right-shifting it by 30 bits, which corresponds to the Page Upper Directory (PUD) index.
    u64 pud_index = (vaddr >> 30) & MASK; 
    // Extracts the next 9 bits of the virtual address after right-shifting it by 21 bits, which corresponds to the Page Middle Directory (PMD) index.
    u64 pmd_index = (vaddr >> 21) & MASK;
    //Extracts the next 9 bits of the virtual address after right-shifting it by 12 bits, which corresponds to the Page Table Entry (PTE) index.
    u64 pte_index = (vaddr >> 12) & MASK; 
   
   u64 *pud, *pmd, *pte;

    // Check if PGD entry is present
    if (!(pgd_base[pgd_index] & PTE_P)) {
        return NULL; // Return NULL if not present
    }

    // Retrieve the PUD base address
      pud = (u64 *)osmap(pgd_base[pgd_index] >> 12);

    // Check if PUD entry is present
    if (!(pud[pud_index] & PTE_P)) {
        return NULL; // Return NULL if not present
    }

    // Retrieve the PMD base address
     pmd = (u64 *)osmap(pud[pud_index] >> 12);

    // Check if PMD entry is present
    if (!(pmd[pmd_index] & PTE_P)) {
        return NULL; // Return NULL if not present
    }

    // Retrieve the PTE base address
     pte = (u64 *)osmap(pmd[pmd_index] >> 12);

    // Check if PTE entry is present
    if (!(pte[pte_index] & PTE_P)) {
        return NULL; // Return NULL if not present
    }

    // Return the address of the PTE entry
    return &pte[pte_index];
}


/*
 * Your Task-1 implementation
 */
// Function to print virtual memory mappings

// Function to print virtual memory mappings
int print_pmaps(struct exec_context *ctx) {
   // printk("you are inside printf_pmaps funtion\n");
  //  printk("Execution Context Details:\n");
   // printk("PID: %u\n", ctx->pid);
    //printk("Name: %s\n", ctx->name);
    u8 j = 0;

    if (!ctx) {
        // return -2;
        printk("Invalid execution context\n");
       
    }
     if (!ctx->mms) {
         
         printk("mms is also null...\n"); 
         return 0;   
       
    }
    
       // printk("MMS is not null\n");
         struct mm_segment *mms = ctx->mms;
        // CODE segment
    printk("%x %x %c%c%c CODE\n", mms[MM_SEG_CODE].start, mms[MM_SEG_CODE].next_free,
           (mms[MM_SEG_CODE].access_flags & MM_RD) ? 'R' : '-',
           (mms[MM_SEG_CODE].access_flags & MM_WR) ? 'W' : '-',
           (mms[MM_SEG_CODE].access_flags & MM_EX) ? 'X' : '-');
    // RODATA segment
    //check for RODATA
    if(mms[MM_SEG_RODATA].start != mms[MM_SEG_RODATA].next_free)
    {
         printk("%x %x %c%c%c RODATA\n", mms[MM_SEG_RODATA].start, mms[MM_SEG_RODATA].next_free,    
           (mms[MM_SEG_RODATA].access_flags & MM_RD) ? 'R' : '-',
           (mms[MM_SEG_RODATA].access_flags & MM_WR) ? 'W' : '-',
           (mms[MM_SEG_RODATA].access_flags & MM_EX) ? 'X' : '-');

    }
    // DATA segment (assuming it's contiguous with CODE segment)
    printk("%x %x %c%c%c DATA\n", mms[MM_SEG_DATA].start, mms[MM_SEG_DATA].next_free,
            (mms[MM_SEG_DATA].access_flags & MM_RD) ? 'R' : '-',
           (mms[MM_SEG_DATA].access_flags & MM_WR) ? 'W' : '-',
           (mms[MM_SEG_DATA].access_flags & MM_EX) ? 'X' : '-');
     


      if (!ctx->vm_area) {
       //  printk("vm_area is null...\n"); 
        return 0;
       }
        //ctx->vm_area->vm_start = MMAP_AREA_START;
        //ctx->vm_area->vm_end = MMAP_AREA_START + PAGE_SIZE;

    //For MMAP
    struct vm_area *curr = ctx->vm_area;
    while (curr) {
        // Determine the permissions
       // printk("you are inside while loop\n");
        // Construct the permissions string directly
        char permissions[4];
        permissions[0] = (curr->access_flags & MM_RD) ? 'R' : '-';
        permissions[1] = (curr->access_flags & MM_WR) ? 'W' : '-';
        permissions[2] = (curr->access_flags & MM_EX) ? 'X' : '-';
        permissions[3] = '\0'; // Null-terminate the string

        // Determine the name based on the starting address
        const char *segment_Name = (curr->vm_start >= MMAP_START && curr->vm_end < STACK_START) ? "MMAP" : "UNKNOWN";

        // Print the information
        printk("%x %x %s %s\n", curr->vm_start, curr->vm_end, permissions, segment_Name);
        // Move to the next VM area
        curr = curr->vm_next;
        //printk("move for next\n");
    }
         // STACK segment
    printk("%x %x %c%c%c STACK\n", mms[MM_SEG_STACK].next_free, mms[MM_SEG_STACK].end,
           (mms[MM_SEG_STACK].access_flags & MM_RD) ? 'R' : '-',
           (mms[MM_SEG_STACK].access_flags & MM_WR) ? 'W' : '-',
           (mms[MM_SEG_STACK].access_flags & MM_EX) ? 'X' : '-');
 
    return 0;
}

/*
 *  Task-2 implementation
 */
/**
 * Function will invoked whenever there is page fault for an address in the vm area region
 * created using mmap
 */
/**
 * Handles page faults that occur within the VM area region created using mmap.
 * This function is invoked whenever there is a page fault for an address in the VM area region.
 *
 * @param current Pointer to the exec_context of the current process
 * @param addr Virtual address that caused the page fault
 * @param error_code Error code associated with the page fault
 * @return 1 if the fault was handled successfully, -1 otherwise
 */
long vm_area_pagefault(struct exec_context *current, u64 addr, int error_code) {
    // Check if the address falls within the mmap area
   if (!(addr >= MMAP_AREA_START && addr < MMAP_AREA_END)) {
        return -1; // Address is outside the mmap area
    }
    // Traverse through the VMAs of the current process
    struct vm_area *current_vma = current->vm_area;
    while (current_vma) {
        // Check if the address belongs to the current VMA
        if (addr >= current_vma->vm_start && addr < current_vma->vm_end) {
          // Determine if it's a write fault and if the VMA allows write access
            int is_write_error = (error_code == 0x6 || error_code == 0x7);
            int vma_allows_write = (current_vma->access_flags & PROT_WRITE);

            if (is_write_error && !vma_allows_write) {
                // Invalid access, return -1
                return -1;
            }
            // Handle copy-on-write fault if error code is 0x7
            if (error_code == 0x7) {
                handle_cow_fault(current, addr, current_vma->access_flags);
                return 1; // Return 1 for a valid access
            }
            // Calculate indexes for different levels of page tables
            u64 *pgd_base = (u64 *)osmap(current->pgd);
            u64 pgd_index = (addr >> 39) & MASK;
            u64 pud_index = (addr >> 30) & MASK;
            u64 pmd_index = (addr >> 21) & MASK;
            u64 pte_index = (addr >> 12) & MASK;

            u64 *pud, *pmd, *pte;

            // If PGD entry is not present, allocate a new PUD
            if (!(pgd_base[pgd_index] & PTE_P)) {
                u32 pud_pfn = os_pfn_alloc(OS_PT_REG);
                pgd_base[pgd_index] = (pud_pfn << 12) | 0x19;
            }
            pud = (u64 *)osmap(pgd_base[pgd_index] >> 12);

            // If PUD entry is not present, allocate a new PMD
            if (!(pud[pud_index] & PTE_P)) {
                u32 pmd_pfn = os_pfn_alloc(OS_PT_REG);
                pud[pud_index] = (pmd_pfn << 12) | 0x19;
            }
            pmd = (u64 *)osmap(pud[pud_index] >> 12);

            // If PMD entry is not present, allocate a new PTE
            if (!(pmd[pmd_index] & PTE_P)) {
                u32 pte_pfn = os_pfn_alloc(OS_PT_REG);
                pmd[pmd_index] = (pte_pfn << 12) | 0x19;
            }
            pte = (u64 *)osmap(pmd[pmd_index] >> 12);

            // If PTE entry is not present, allocate a new physical page frame
            if (!(pte[pte_index] & PTE_P)) {
                u32 page_frame_pfn = os_pfn_alloc(USER_REG);
                if (current_vma->access_flags != (PROT_READ | PROT_WRITE)) {
                    pte[pte_index] = (page_frame_pfn << 12) | 0x11;
                } else {
                    pte[pte_index] = (page_frame_pfn << 12) | 0x19;
                }
            }

      
            // Fault handled successfully
            return 1;
        }
        // Move to the next VMA
        current_vma = current_vma->vm_next;
    }

    // Address does not belong to any VMA, return -1
    return -1;
}


/*
 *  Task-3 implementation
 */
/**
 * mprotect System call Implementation.
 *  *
 * @param current Pointer to the exec_context of the current process
 * @param addr Virtual address that caused the page fault
 * @param length The length of the memory region to modify protection for, specified in bytes.
 * @param prot representing the new protection flags to set for the specified memory region.
 * @return 1 if the fault was handled successfully, -1 otherwise
 */

long vm_area_mprotect(struct exec_context *current, u64 addr, int length, int prot) {    
     // Check if the address range is within the mmap area and length is positive
    if (addr < MMAP_AREA_START || addr >= MMAP_AREA_END || length <= 0) {
        return -EINVAL;
    }

       // Check if PROT_EXEC is set
    if (prot & PROT_EXEC) {
        return -EINVAL;
    }

        // Check if prot is either PROT_READ or (PROT_READ | PROT_WRITE)
    if (!(prot == PROT_READ || prot == (PROT_READ | PROT_WRITE))) {
        return -EINVAL;
    }

    // Adjust the length to be a multiple of PAGE_SIZE
    if (length % PAGE_SIZE) {
        length = (length / PAGE_SIZE + 1) * PAGE_SIZE;
    }

        // Calculate the end address of the range to be modified
        u64 mprotect_end = addr + length;
        // Initialize a pointer to the first vm_area in the linked list
        // of memory areas associated with the current process
        struct vm_area *vma = current->vm_area;
        // Initialize a pointer to keep track of the previous vm_area node
        struct vm_area *prev_vma = NULL;


    int vm_area_changed = 0;

   while (vma) {
        if (vma->vm_end <= addr || vma->vm_start >= mprotect_end) {
            prev_vma = vma;
            vma = vma->vm_next;
            continue;
        }

        if (addr <= vma->vm_start && mprotect_end >= vma->vm_end) {
            vma->access_flags = prot;
            vm_area_changed = 1;
            u64 start_addr = (vma->vm_start > addr) ? vma->vm_start : addr;
            u64 end_addr = (vma->vm_end < mprotect_end) ? vma->vm_end : mprotect_end;

            for (u64 page_addr = start_addr; page_addr < end_addr; page_addr += PAGE_SIZE) {
                u64 *pte = get_pte_entry(current->pgd, page_addr);
                if (pte && (*pte & PTE_PRESENT)) {
                    if (prot == PROT_WRITE || prot == (PROT_READ | PROT_WRITE)) {
                        if(get_pfn_refcount((*pte & PTE_PFN_MASK) >> 12) == 1){
                            *pte |= PTE_RW_BIT;
                        }else{
                            continue;
                        }
                    } else {
                        *pte &= ~PTE_RW_BIT;
                    }
                }
            }
        } else if (addr > vma->vm_start && mprotect_end < vma->vm_end) {
            struct vm_area *new_vma1 = os_alloc(sizeof(struct vm_area));
            struct vm_area *new_vma2 = os_alloc(sizeof(struct vm_area));
            if (!new_vma1 || !new_vma2) {
                return -EINVAL;
            }

            *new_vma1 = *vma;
            *new_vma2 = *vma;
            new_vma1->vm_end = addr;
            new_vma2->vm_start = mprotect_end;
            vma->vm_start = addr;
            vma->vm_end = mprotect_end;
            vma->access_flags = prot;

            new_vma2->vm_next = vma->vm_next;
            vma->vm_next = new_vma2;
            new_vma1->vm_next = vma;
            if (prev_vma) {
                prev_vma->vm_next = new_vma1;
            } else {
                current->vm_area = new_vma1;
            }

            stats->num_vm_area += 2;
            u64 start_addr = (vma->vm_start > addr) ? vma->vm_start : addr;
            u64 end_addr = (vma->vm_end < mprotect_end) ? vma->vm_end : mprotect_end;

            for (u64 page_addr = start_addr; page_addr < end_addr; page_addr += PAGE_SIZE) {
                u64 *pte = get_pte_entry(current->pgd, page_addr);
                if (pte && (*pte & PTE_PRESENT)) {
                    if (prot == PROT_WRITE || prot == (PROT_READ | PROT_WRITE)) {
                        if(get_pfn_refcount((*pte & PTE_PFN_MASK) >> 12) == 1){
                            *pte |= PTE_RW_BIT;
                        }else{
                            continue;
                        }
                    } else {
                        *pte &= ~PTE_RW_BIT;
                    }
                }
            }
            vm_area_changed = 1;
            break;
        } else {
            if (vma->vm_start < addr) {
                struct vm_area *new_vma = os_alloc(sizeof(struct vm_area));
                if (!new_vma) {
                    return -EINVAL;
                }
                *new_vma = *vma;
                new_vma->vm_start = addr;
                vma->vm_end = addr;
                new_vma->vm_next = vma->vm_next;
                vma->vm_next = new_vma;
                stats->num_vm_area++;
                vma = new_vma;
            }

            if (vma->vm_end > mprotect_end) {
                struct vm_area *new_vma = os_alloc(sizeof(struct vm_area));
                if (!new_vma) {
                    return -EINVAL;
                }
                *new_vma = *vma;
                new_vma->vm_end = vma->vm_end;
                new_vma->vm_start = mprotect_end;
                vma->vm_end = mprotect_end;
                new_vma->vm_next = vma->vm_next;
                vma->vm_next = new_vma;
                stats->num_vm_area++;
            }

            vma->access_flags = prot;
            vm_area_changed = 1;

            u64 start_addr = (vma->vm_start > addr) ? vma->vm_start : addr;
            u64 end_addr = (vma->vm_end < mprotect_end) ? vma->vm_end : mprotect_end;

            for (u64 page_addr = start_addr; page_addr < end_addr; page_addr += PAGE_SIZE) {
                u64 *pte = get_pte_entry(current->pgd, page_addr);
                if (pte && (*pte & PTE_PRESENT)) {
                    if (prot == PROT_WRITE || prot == (PROT_READ | PROT_WRITE)) {
                        if(get_pfn_refcount((*pte & PTE_PFN_MASK) >> 12) == 1){
                            *pte |= PTE_RW_BIT;
                        }else{
                            continue;
                        }
                    } else {
                        *pte &= ~PTE_RW_BIT;
                    }
                }
            }
        }

        if (prev_vma && prev_vma->vm_end == vma->vm_start && prev_vma->access_flags == vma->access_flags) {
            prev_vma->vm_end = vma->vm_end;
            prev_vma->vm_next = vma->vm_next;
            os_free(vma, sizeof(struct vm_area));
            stats->num_vm_area--;
            vma = prev_vma->vm_next;
        } else {
        if (vma->vm_next && vma->vm_end == vma->vm_next->vm_start && vma->access_flags == vma->vm_next->access_flags) {
            struct vm_area *next_vma = vma->vm_next;
            vma->vm_end = next_vma->vm_end;
            vma->vm_next = next_vma->vm_next;
            os_free(next_vma, sizeof(struct vm_area));
            stats->num_vm_area--;
    }
        prev_vma = vma;
        vma = vma->vm_next;
}
    }

    flush_table();
    return vm_area_changed ? 0 : -1;
}
