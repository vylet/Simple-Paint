int SaveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight)
	
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	unsigned char *ptrImage = (unsigned char*)malloc(
		sizeof(unsigned char) * nWidth * nHeight * 3
		+ (4 - (3 * nWidth) % 4) * nHeight);
	FILE *ptrFile = fopen(ptrcFileName, "wb");
	//read pixels from framebuffer
	glReadPixels(nX, nY, nWidth, nHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE,
		ptrImage);
	// set memory buffer for bitmap header and informaiton header
	memset(&bf, 0, sizeof(bf));
	memset(&bi, 0, sizeof(bi));
	// configure the headers with the give parameters
	bf.bfType = 0x4d42;
	bf.bfSize = sizeof(bf) + sizeof(bi) + nWidth * nHeight * 3
		+ (4 - (3 * nWidth) % 4) * nHeight;
	bf.bfOffBits = sizeof(bf) + sizeof(bi);
	bi.biSize = sizeof(bi);
	bi.biWidth = nWidth + nWidth % 4;
	bi.biHeight = nHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biSizeImage = nWidth * nHeight * 3 + (4 - (3 * nWidth) % 4) * nHeight;
	// to files
	fwrite(&bf, sizeof(bf), 1, ptrFile);
	fwrite(&bi, sizeof(bi), 1, ptrFile);
	fwrite(ptrImage, sizeof(unsigned char),
		nWidth * nHeight * 3 + (4 - (3 * nWidth) % 4) * nHeight, ptrFile);
	fclose(ptrFile);
	free(ptrImage);
	return 0;
}