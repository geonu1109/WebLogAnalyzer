//#include "FileProc.h"
//#include <cstdlib>
//
//FileProc::FileProc()
//{
//}
//
//FileProc::~FileProc()
//{
//}
//
//FILE *FileProc::open(const char *path, const char *mode) {
//	FILE *fp = fopen(path, mode);
//	if (fp) return fp;
//	else {
//		printf("\n[Error] Failed to open file '%s'\n\n", path);
//		system("pause");
//	}
//}
//
//void FileProc::close(FILE *fp) {
//	fclose(fp);
//}