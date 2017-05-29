#pragma once

#define SAFE_DELETE(buffer) if(buffer) delete buffer; buffer = nullptr;
#define SAFE_RELEASE(buffer) if(buffer) buffer->Release(); buffer = nullptr;
#define SAFE_DELARRY(buffer) if(buffer) delete[] buffer; buffer = nullptr;