/*! \file pagefaultmanager.cc
Routines for the page fault managerPage Fault Manager
*/
//
//  Copyright (c) 1999-2000 INSA de Rennes.
//  All rights reserved.  
//  See copyright_insa.h for copyright notice and limitation 
//  of liability and disclaimer of warranty provisions.
//

#include "kernel/thread.h"
#include "vm/swapManager.h"
#include "vm/physMem.h"
#include "vm/pagefaultmanager.h"

PageFaultManager::PageFaultManager() {
}

// PageFaultManager::~PageFaultManager()
/*! Nothing for now
*/
PageFaultManager::~PageFaultManager() {
}

// ExceptionType PageFault(int virtualPage)
/*! 	
//	This method is called by the Memory Management Unit when there is a 
//      page fault. This method loads the page from :
//      - read-only sections (text,rodata) $\Rightarrow$ executive
//        file
//      - read/write sections (data,...) $\Rightarrow$ executive
//        file (1st time only), or swap file
//      - anonymous mappings (stack/bss) $\Rightarrow$ new
//        page from the MemoryManager (1st time only), or swap file
//
//	\param virtualPage the virtual page subject to the page fault
//	  (supposed to be between 0 and the
//        size of the address space, and supposed to correspond to a
//        page mapped to something [code/data/bss/...])
//	\return the exception (generally the NO_EXCEPTION constant)
*/
#ifndef ETUDIANTS_TP
ExceptionType PageFaultManager::PageFault(int virtualPage) 
{
  printf("**** Warning: page fault manager is not implemented yet\n");
    exit(-1);
    return ((ExceptionType)0);
}
#endif

#ifdef ETUDIANTS_TP
ExceptionType PageFaultManager::PageFault(int virtualPage) {

	// Assert that the page is not yet valid
	ASSERT(!g_machine->mmu->translationTable->getBitValid(virtualPage));

	// TODO: Normally, we only deal with temporary pages here

	// If it's stored in the swap
	if (g_machine->mmu->translationTable->getBitSwap(virtualPage)) {

		// TODO: Maybe another way to do this
		// A page stealer is dealing with the current page
		while (g_machine->mmu->translationTable->getAddrDisk(virtualPage) == -1);

		// Get the real page from the swap
		g_swap_manager->GetPageSwap(g_machine->mmu->translationTable->getAddrDisk(virtualPage), (int *)&g_machine->mainMemory[g_machine->mmu->translationTable->getPhysicalPage(virtualPage) * g_cfg->PageSize]); 

	} else {  // If stored in the disk

		// If anonymous page
		if (g_machine->mmu->translationTable->getAddrDisk(virtualPage) == -1) {
			
			// Fill with 0
			memset(&(g_machine->mainMemory[g_machine->mmu->translationTable->getPhysicalPage(virtualPage) * g_cfg->PageSize]), 0, g_cfg->PageSize);
		
		} else {

			// Load the executive
			if (!g_machine->mmu->ReadMem(virtualPage, g_cfg->PageSize, (int *)&g_machine->mainMemory[g_machine->mmu->translationTable->getPhysicalPage(virtualPage) * g_cfg->PageSize], false)) {
				DEBUG('d', (char *)"Page fault on a virtual page that doesn't allow read");
				return PAGEFAULT_EXCEPTION;
			}

		}

	}

	// If everything's fine
	return NO_EXCEPTION;

}
#endif