#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"
#include "user_interface.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1

uint8 my_key[] = {
  0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e, 0x20, 0x52,
  0x53, 0x41, 0x20, 0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4b,
  0x45, 0x59, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49, 0x49, 0x43,
  0x58, 0x51, 0x49, 0x42, 0x41, 0x41, 0x4b, 0x42, 0x67, 0x51, 0x44, 0x52,
  0x55, 0x66, 0x43, 0x33, 0x35, 0x48, 0x76, 0x79, 0x45, 0x44, 0x6a, 0x52,
  0x72, 0x73, 0x44, 0x2f, 0x37, 0x59, 0x56, 0x49, 0x69, 0x59, 0x45, 0x6c,
  0x79, 0x46, 0x44, 0x53, 0x53, 0x57, 0x53, 0x41, 0x65, 0x69, 0x6d, 0x46,
  0x4d, 0x4a, 0x77, 0x32, 0x73, 0x69, 0x4e, 0x48, 0x72, 0x57, 0x51, 0x74,
  0x0a, 0x6e, 0x66, 0x34, 0x59, 0x77, 0x30, 0x4d, 0x75, 0x52, 0x73, 0x4e,
  0x35, 0x6b, 0x61, 0x36, 0x57, 0x76, 0x2b, 0x51, 0x66, 0x66, 0x59, 0x2f,
  0x45, 0x64, 0x34, 0x63, 0x41, 0x6f, 0x4a, 0x30, 0x31, 0x54, 0x75, 0x50,
  0x34, 0x58, 0x31, 0x53, 0x6b, 0x54, 0x50, 0x73, 0x45, 0x6a, 0x68, 0x50,
  0x72, 0x75, 0x59, 0x73, 0x62, 0x57, 0x57, 0x2b, 0x6e, 0x43, 0x46, 0x4e,
  0x37, 0x4f, 0x4a, 0x67, 0x69, 0x0a, 0x4e, 0x62, 0x47, 0x2b, 0x55, 0x63,
  0x2b, 0x56, 0x37, 0x77, 0x36, 0x46, 0x4f, 0x67, 0x79, 0x2b, 0x36, 0x41,
  0x31, 0x38, 0x2f, 0x6a, 0x78, 0x2f, 0x6b, 0x62, 0x67, 0x74, 0x6f, 0x50,
  0x61, 0x71, 0x51, 0x67, 0x37, 0x49, 0x34, 0x55, 0x5a, 0x6b, 0x49, 0x61,
  0x30, 0x6d, 0x4c, 0x6d, 0x51, 0x58, 0x7a, 0x66, 0x32, 0x6e, 0x50, 0x5a,
  0x2f, 0x4e, 0x34, 0x51, 0x49, 0x44, 0x41, 0x51, 0x41, 0x42, 0x0a, 0x41,
  0x6f, 0x47, 0x42, 0x41, 0x4b, 0x4e, 0x42, 0x34, 0x4a, 0x6a, 0x63, 0x32,
  0x52, 0x73, 0x63, 0x4d, 0x65, 0x54, 0x42, 0x41, 0x77, 0x44, 0x5a, 0x6c,
  0x57, 0x6e, 0x55, 0x37, 0x57, 0x69, 0x31, 0x69, 0x75, 0x76, 0x6f, 0x6d,
  0x44, 0x31, 0x6f, 0x69, 0x6e, 0x65, 0x36, 0x53, 0x53, 0x79, 0x54, 0x31,
  0x64, 0x5a, 0x79, 0x30, 0x7a, 0x36, 0x4e, 0x43, 0x6f, 0x44, 0x76, 0x30,
  0x72, 0x63, 0x47, 0x0a, 0x4e, 0x44, 0x48, 0x65, 0x51, 0x53, 0x69, 0x4d,
  0x73, 0x2f, 0x55, 0x6e, 0x72, 0x6e, 0x6b, 0x53, 0x72, 0x4c, 0x58, 0x39,
  0x6a, 0x33, 0x2f, 0x6a, 0x62, 0x77, 0x4f, 0x41, 0x35, 0x46, 0x30, 0x38,
  0x35, 0x43, 0x64, 0x62, 0x66, 0x64, 0x5a, 0x68, 0x36, 0x72, 0x52, 0x30,
  0x4e, 0x38, 0x38, 0x46, 0x53, 0x76, 0x58, 0x39, 0x32, 0x4e, 0x7a, 0x4c,
  0x47, 0x47, 0x43, 0x4c, 0x54, 0x69, 0x73, 0x39, 0x0a, 0x44, 0x61, 0x76,
  0x4a, 0x71, 0x70, 0x77, 0x6e, 0x76, 0x43, 0x74, 0x62, 0x39, 0x62, 0x4a,
  0x34, 0x4c, 0x43, 0x66, 0x57, 0x4e, 0x57, 0x2b, 0x67, 0x7a, 0x67, 0x62,
  0x39, 0x5a, 0x76, 0x58, 0x65, 0x55, 0x66, 0x7a, 0x55, 0x55, 0x68, 0x55,
  0x71, 0x30, 0x57, 0x59, 0x66, 0x47, 0x41, 0x67, 0x52, 0x41, 0x6b, 0x45,
  0x41, 0x36, 0x4f, 0x31, 0x46, 0x6c, 0x4b, 0x68, 0x52, 0x56, 0x71, 0x61,
  0x33, 0x0a, 0x38, 0x56, 0x67, 0x74, 0x53, 0x6d, 0x65, 0x37, 0x39, 0x4f,
  0x4f, 0x34, 0x63, 0x49, 0x78, 0x66, 0x57, 0x66, 0x4b, 0x6c, 0x57, 0x68,
  0x45, 0x76, 0x52, 0x78, 0x58, 0x53, 0x4b, 0x37, 0x71, 0x48, 0x69, 0x68,
  0x57, 0x69, 0x72, 0x59, 0x41, 0x6d, 0x51, 0x6f, 0x73, 0x6b, 0x61, 0x76,
  0x76, 0x44, 0x61, 0x49, 0x68, 0x67, 0x44, 0x48, 0x35, 0x6b, 0x4e, 0x4d,
  0x71, 0x61, 0x47, 0x61, 0x6b, 0x65, 0x0a, 0x4e, 0x53, 0x43, 0x46, 0x65,
  0x37, 0x36, 0x71, 0x6e, 0x51, 0x4a, 0x42, 0x41, 0x4f, 0x59, 0x4f, 0x42,
  0x2f, 0x48, 0x57, 0x4b, 0x58, 0x31, 0x59, 0x76, 0x37, 0x73, 0x49, 0x47,
  0x68, 0x6f, 0x72, 0x43, 0x51, 0x34, 0x67, 0x75, 0x6d, 0x32, 0x7a, 0x6f,
  0x62, 0x51, 0x63, 0x48, 0x52, 0x38, 0x4a, 0x45, 0x54, 0x61, 0x53, 0x33,
  0x48, 0x55, 0x2b, 0x75, 0x74, 0x56, 0x6d, 0x57, 0x78, 0x51, 0x59, 0x0a,
  0x51, 0x36, 0x6e, 0x37, 0x79, 0x67, 0x64, 0x32, 0x4a, 0x47, 0x56, 0x4c,
  0x4e, 0x6c, 0x58, 0x50, 0x69, 0x6e, 0x62, 0x44, 0x75, 0x76, 0x50, 0x47,
  0x72, 0x70, 0x61, 0x4e, 0x57, 0x44, 0x37, 0x4f, 0x57, 0x78, 0x55, 0x43,
  0x51, 0x51, 0x43, 0x76, 0x39, 0x45, 0x56, 0x43, 0x74, 0x68, 0x2b, 0x7a,
  0x71, 0x48, 0x39, 0x39, 0x6c, 0x6c, 0x47, 0x6f, 0x53, 0x6c, 0x4b, 0x47,
  0x2f, 0x4e, 0x73, 0x67, 0x0a, 0x55, 0x6a, 0x6e, 0x5a, 0x64, 0x64, 0x34,
  0x49, 0x2b, 0x73, 0x42, 0x50, 0x48, 0x36, 0x48, 0x44, 0x6e, 0x4d, 0x57,
  0x30, 0x76, 0x77, 0x46, 0x44, 0x74, 0x58, 0x47, 0x78, 0x68, 0x50, 0x43,
  0x2b, 0x7a, 0x47, 0x37, 0x68, 0x38, 0x56, 0x73, 0x31, 0x4e, 0x4f, 0x6b,
  0x33, 0x6f, 0x2f, 0x44, 0x69, 0x2f, 0x34, 0x6b, 0x74, 0x4d, 0x75, 0x4d,
  0x44, 0x42, 0x70, 0x5a, 0x56, 0x41, 0x6b, 0x41, 0x4c, 0x0a, 0x2f, 0x71,
  0x56, 0x4a, 0x5a, 0x61, 0x6f, 0x71, 0x48, 0x2b, 0x74, 0x33, 0x4f, 0x2f,
  0x66, 0x6f, 0x62, 0x31, 0x2f, 0x38, 0x66, 0x5a, 0x5a, 0x61, 0x79, 0x2b,
  0x66, 0x64, 0x64, 0x53, 0x33, 0x4c, 0x68, 0x58, 0x53, 0x42, 0x54, 0x4f,
  0x7a, 0x7a, 0x71, 0x2f, 0x36, 0x66, 0x79, 0x38, 0x4e, 0x70, 0x36, 0x38,
  0x33, 0x7a, 0x57, 0x65, 0x35, 0x78, 0x72, 0x79, 0x59, 0x38, 0x70, 0x63,
  0x78, 0x43, 0x0a, 0x63, 0x78, 0x79, 0x38, 0x44, 0x6e, 0x35, 0x37, 0x34,
  0x56, 0x73, 0x4f, 0x2f, 0x48, 0x57, 0x69, 0x61, 0x4b, 0x33, 0x31, 0x41,
  0x6b, 0x41, 0x4e, 0x32, 0x64, 0x4a, 0x32, 0x66, 0x78, 0x70, 0x77, 0x57,
  0x2f, 0x47, 0x72, 0x36, 0x66, 0x31, 0x42, 0x34, 0x7a, 0x49, 0x34, 0x30,
  0x42, 0x62, 0x43, 0x76, 0x6b, 0x33, 0x77, 0x56, 0x72, 0x46, 0x75, 0x4e,
  0x2b, 0x43, 0x31, 0x77, 0x67, 0x68, 0x37, 0x0a, 0x30, 0x46, 0x76, 0x56,
  0x74, 0x7a, 0x66, 0x45, 0x2b, 0x46, 0x59, 0x78, 0x4d, 0x63, 0x78, 0x76,
  0x58, 0x5a, 0x54, 0x30, 0x39, 0x62, 0x55, 0x56, 0x63, 0x66, 0x74, 0x6a,
  0x31, 0x65, 0x4e, 0x7a, 0x2f, 0x41, 0x78, 0x67, 0x66, 0x62, 0x57, 0x50,
  0x52, 0x53, 0x45, 0x35, 0x0a, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x45, 0x4e,
  0x44, 0x20, 0x52, 0x53, 0x41, 0x20, 0x50, 0x52, 0x49, 0x56, 0x41, 0x54,
  0x45, 0x20, 0x4b, 0x45, 0x59, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
};

uint8 my_cert[] = {
  0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e, 0x20, 0x43,
  0x45, 0x52, 0x54, 0x49, 0x46, 0x49, 0x43, 0x41, 0x54, 0x45, 0x2d, 0x2d,
  0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49, 0x49, 0x43, 0x4d, 0x6a, 0x43, 0x43,
  0x41, 0x5a, 0x75, 0x67, 0x41, 0x77, 0x49, 0x42, 0x41, 0x67, 0x49, 0x4a,
  0x41, 0x4c, 0x46, 0x2b, 0x71, 0x4a, 0x75, 0x69, 0x77, 0x32, 0x34, 0x38,
  0x4d, 0x41, 0x30, 0x47, 0x43, 0x53, 0x71, 0x47, 0x53, 0x49, 0x62, 0x33,
  0x44, 0x51, 0x45, 0x42, 0x43, 0x77, 0x55, 0x41, 0x4d, 0x44, 0x49, 0x78,
  0x45, 0x54, 0x41, 0x50, 0x42, 0x67, 0x4e, 0x56, 0x0a, 0x42, 0x41, 0x4d,
  0x4d, 0x43, 0x45, 0x70, 0x76, 0x61, 0x47, 0x34, 0x67, 0x52, 0x47, 0x39,
  0x6c, 0x4d, 0x52, 0x30, 0x77, 0x47, 0x77, 0x59, 0x4a, 0x4b, 0x6f, 0x5a,
  0x49, 0x68, 0x76, 0x63, 0x4e, 0x41, 0x51, 0x6b, 0x42, 0x46, 0x67, 0x35,
  0x71, 0x5a, 0x45, 0x42, 0x6c, 0x65, 0x47, 0x46, 0x74, 0x63, 0x47, 0x78,
  0x6c, 0x4c, 0x6d, 0x56, 0x6b, 0x64, 0x54, 0x41, 0x65, 0x46, 0x77, 0x30,
  0x78, 0x0a, 0x4e, 0x54, 0x45, 0x79, 0x4d, 0x6a, 0x45, 0x79, 0x4d, 0x6a,
  0x49, 0x33, 0x4d, 0x54, 0x42, 0x61, 0x46, 0x77, 0x30, 0x78, 0x4e, 0x6a,
  0x41, 0x78, 0x4d, 0x6a, 0x41, 0x79, 0x4d, 0x6a, 0x49, 0x33, 0x4d, 0x54,
  0x42, 0x61, 0x4d, 0x44, 0x49, 0x78, 0x45, 0x54, 0x41, 0x50, 0x42, 0x67,
  0x4e, 0x56, 0x42, 0x41, 0x4d, 0x4d, 0x43, 0x45, 0x70, 0x76, 0x61, 0x47,
  0x34, 0x67, 0x52, 0x47, 0x39, 0x6c, 0x0a, 0x4d, 0x52, 0x30, 0x77, 0x47,
  0x77, 0x59, 0x4a, 0x4b, 0x6f, 0x5a, 0x49, 0x68, 0x76, 0x63, 0x4e, 0x41,
  0x51, 0x6b, 0x42, 0x46, 0x67, 0x35, 0x71, 0x5a, 0x45, 0x42, 0x6c, 0x65,
  0x47, 0x46, 0x74, 0x63, 0x47, 0x78, 0x6c, 0x4c, 0x6d, 0x56, 0x6b, 0x64,
  0x54, 0x43, 0x42, 0x6e, 0x7a, 0x41, 0x4e, 0x42, 0x67, 0x6b, 0x71, 0x68,
  0x6b, 0x69, 0x47, 0x39, 0x77, 0x30, 0x42, 0x41, 0x51, 0x45, 0x46, 0x0a,
  0x41, 0x41, 0x4f, 0x42, 0x6a, 0x51, 0x41, 0x77, 0x67, 0x59, 0x6b, 0x43,
  0x67, 0x59, 0x45, 0x41, 0x30, 0x56, 0x48, 0x77, 0x74, 0x2b, 0x52, 0x37,
  0x38, 0x68, 0x41, 0x34, 0x30, 0x61, 0x37, 0x41, 0x2f, 0x2b, 0x32, 0x46,
  0x53, 0x49, 0x6d, 0x42, 0x4a, 0x63, 0x68, 0x51, 0x30, 0x6b, 0x6c, 0x6b,
  0x67, 0x48, 0x6f, 0x70, 0x68, 0x54, 0x43, 0x63, 0x4e, 0x72, 0x49, 0x6a,
  0x52, 0x36, 0x31, 0x6b, 0x0a, 0x4c, 0x5a, 0x33, 0x2b, 0x47, 0x4d, 0x4e,
  0x44, 0x4c, 0x6b, 0x62, 0x44, 0x65, 0x5a, 0x47, 0x75, 0x6c, 0x72, 0x2f,
  0x6b, 0x48, 0x33, 0x32, 0x50, 0x78, 0x48, 0x65, 0x48, 0x41, 0x4b, 0x43,
  0x64, 0x4e, 0x55, 0x37, 0x6a, 0x2b, 0x46, 0x39, 0x55, 0x70, 0x45, 0x7a,
  0x37, 0x42, 0x49, 0x34, 0x54, 0x36, 0x37, 0x6d, 0x4c, 0x47, 0x31, 0x6c,
  0x76, 0x70, 0x77, 0x68, 0x54, 0x65, 0x7a, 0x69, 0x59, 0x0a, 0x49, 0x6a,
  0x57, 0x78, 0x76, 0x6c, 0x48, 0x50, 0x6c, 0x65, 0x38, 0x4f, 0x68, 0x54,
  0x6f, 0x4d, 0x76, 0x75, 0x67, 0x4e, 0x66, 0x50, 0x34, 0x38, 0x66, 0x35,
  0x47, 0x34, 0x4c, 0x61, 0x44, 0x32, 0x71, 0x6b, 0x49, 0x4f, 0x79, 0x4f,
  0x46, 0x47, 0x5a, 0x43, 0x47, 0x74, 0x4a, 0x69, 0x35, 0x6b, 0x46, 0x38,
  0x33, 0x39, 0x70, 0x7a, 0x32, 0x66, 0x7a, 0x65, 0x45, 0x43, 0x41, 0x77,
  0x45, 0x41, 0x0a, 0x41, 0x61, 0x4e, 0x51, 0x4d, 0x45, 0x34, 0x77, 0x48,
  0x51, 0x59, 0x44, 0x56, 0x52, 0x30, 0x4f, 0x42, 0x42, 0x59, 0x45, 0x46,
  0x41, 0x64, 0x38, 0x4a, 0x6c, 0x58, 0x45, 0x68, 0x70, 0x2f, 0x34, 0x6d,
  0x4f, 0x6b, 0x49, 0x73, 0x46, 0x5a, 0x69, 0x73, 0x74, 0x39, 0x56, 0x41,
  0x6b, 0x58, 0x7a, 0x4d, 0x42, 0x38, 0x47, 0x41, 0x31, 0x55, 0x64, 0x49,
  0x77, 0x51, 0x59, 0x4d, 0x42, 0x61, 0x41, 0x0a, 0x46, 0x41, 0x64, 0x38,
  0x4a, 0x6c, 0x58, 0x45, 0x68, 0x70, 0x2f, 0x34, 0x6d, 0x4f, 0x6b, 0x49,
  0x73, 0x46, 0x5a, 0x69, 0x73, 0x74, 0x39, 0x56, 0x41, 0x6b, 0x58, 0x7a,
  0x4d, 0x41, 0x77, 0x47, 0x41, 0x31, 0x55, 0x64, 0x45, 0x77, 0x51, 0x46,
  0x4d, 0x41, 0x4d, 0x42, 0x41, 0x66, 0x38, 0x77, 0x44, 0x51, 0x59, 0x4a,
  0x4b, 0x6f, 0x5a, 0x49, 0x68, 0x76, 0x63, 0x4e, 0x41, 0x51, 0x45, 0x4c,
  0x0a, 0x42, 0x51, 0x41, 0x44, 0x67, 0x59, 0x45, 0x41, 0x79, 0x59, 0x2f,
  0x56, 0x4f, 0x53, 0x4e, 0x2b, 0x71, 0x56, 0x75, 0x57, 0x46, 0x49, 0x38,
  0x6d, 0x65, 0x63, 0x30, 0x49, 0x6f, 0x34, 0x6f, 0x4b, 0x6a, 0x73, 0x61,
  0x4d, 0x6c, 0x4a, 0x72, 0x7a, 0x55, 0x4f, 0x67, 0x47, 0x38, 0x73, 0x44,
  0x35, 0x66, 0x66, 0x37, 0x37, 0x44, 0x65, 0x65, 0x72, 0x32, 0x54, 0x39,
  0x49, 0x47, 0x67, 0x6c, 0x7a, 0x0a, 0x70, 0x63, 0x49, 0x58, 0x74, 0x59,
  0x78, 0x2b, 0x74, 0x55, 0x45, 0x6c, 0x37, 0x58, 0x6d, 0x2f, 0x39, 0x2f,
  0x37, 0x69, 0x52, 0x66, 0x63, 0x30, 0x4d, 0x58, 0x70, 0x35, 0x68, 0x6b,
  0x56, 0x2f, 0x46, 0x76, 0x31, 0x52, 0x61, 0x32, 0x68, 0x32, 0x30, 0x31,
  0x67, 0x45, 0x37, 0x48, 0x41, 0x43, 0x65, 0x69, 0x67, 0x36, 0x47, 0x33,
  0x6b, 0x64, 0x48, 0x43, 0x69, 0x38, 0x75, 0x43, 0x76, 0x30, 0x0a, 0x35,
  0x59, 0x5a, 0x51, 0x56, 0x61, 0x42, 0x73, 0x41, 0x6c, 0x49, 0x39, 0x62,
  0x42, 0x62, 0x2b, 0x38, 0x50, 0x51, 0x75, 0x4d, 0x45, 0x50, 0x36, 0x59,
  0x6b, 0x54, 0x51, 0x4b, 0x47, 0x66, 0x6a, 0x63, 0x74, 0x7a, 0x65, 0x42,
  0x72, 0x6c, 0x35, 0x36, 0x50, 0x70, 0x6c, 0x62, 0x41, 0x58, 0x4b, 0x77,
  0x2b, 0x30, 0x3d, 0x0a, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x45, 0x4e, 0x44,
  0x20, 0x43, 0x45, 0x52, 0x54, 0x49, 0x46, 0x49, 0x43, 0x41, 0x54, 0x45,
  0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
};

os_event_t    user_procTaskQueue[user_procTaskQueueLen];
static void loop(os_event_t *events);

//Main code function
static void ICACHE_FLASH_ATTR
loop(os_event_t *events)
{
    os_printf("Hello\n\r");
    os_delay_us(10000);
    system_os_post(user_procTaskPrio, 0, 0 );
}

//Init function 
void ICACHE_FLASH_ATTR
user_init()
{
    char ssid[32] = SSID;
    char password[64] = SSID_PASSWORD;
    struct station_config stationConf;
    uint32 free;

    //Set station mode
    wifi_set_opmode( 0x1 );

    //Set ap settings
    os_memcpy(&stationConf.ssid, ssid, 32);
    os_memcpy(&stationConf.password, password, 64);
    wifi_station_set_config(&stationConf);

    free = system_get_free_heap_size();

    if( wifi_station_set_cert_key(my_cert, strlen(my_cert), my_key, strlen(my_key), NULL, 0) == 0 ) {
        os_printf("Hello eduroam\n\r");
    }
    wifi_station_clear_cert_key();

    //Start os task
    system_os_task(loop, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);

    system_os_post(user_procTaskPrio, 0, 0 );
}
