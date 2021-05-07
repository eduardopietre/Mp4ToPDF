#include "PDFWriter.h"

bool PDFWriter::Write() {
	std::string device = "DeviceRGB";

	int lenImages = _images.size();
	int no_j = 3 + lenImages * 2;

	std::vector<fpos_t> objp;
	FILE* fp;
	fopen_s(&fp, _filename.c_str(), "wb");

	fprintf(fp, "%%PDF-1.2\r\n");
	fprintf(fp, "\r\n");
	AddPosInVector(fp, &objp);

	fprintf(fp, "1 0 obj\r\n");
	fprintf(fp, "<<\r\n");
	fprintf(fp, "  /Type /Catalog /Pages 2 0 R\r\n");
	fprintf(fp, ">>\r\n");
	fprintf(fp, "endobj\r\n");
	fprintf(fp, "\r\n");
	AddPosInVector(fp, &objp);

	fprintf(fp, "2 0 obj\r\n");
	fprintf(fp, "<<\r\n");
	fprintf(fp, "  /Type /Pages /Count %d\r\n", lenImages);
	fprintf(fp, "  /Kids\r\n");
	fprintf(fp, "  [");

	for (int i = 0; i < lenImages; i++)
	{
		if ((i & 7) == 0)
		{
			fprintf(fp, "\r\n");
			fprintf(fp, "   ");
		}
		fprintf(fp, " %d 0 R", 3 + i * 2);
	}

	fprintf(fp, "\r\n");
	fprintf(fp, "  ]\r\n");
	fprintf(fp, ">>\r\n");
	fprintf(fp, "endobj\r\n");

	for (int i = 0; i < lenImages; i++) {
		int no_p = 3 + i * 2;
		int no_c = no_p + 1;
		std::string name = "/Jpeg" + std::to_string(i + 1);

		JpegImage image(_images.at(i));
		cv::Size size = image.Size();
		EncodedImageSize* encodedSize = image.GetEncodedImageSize();

		fprintf(fp, "\r\n");
		AddPosInVector(fp, &objp);
		fprintf(fp, "%d 0 obj\r\n", no_p);
		fprintf(fp, "<<\r\n");
		fprintf(fp, "  /Type /Page /Parent 2 0 R /Contents %d 0 R\r\n", no_c);
		fprintf(fp, "  /MediaBox [ 0 0 %d %d ]\r\n", size.width, size.height);

		fprintf(fp, "  /Resources\r\n");
		fprintf(fp, "  <<\r\n");
		fprintf(fp, "    /ProcSet [ /PDF /ImageB /ImageC /ImageI ]\r\n");
		fprintf(fp, "    /XObject << %s %d 0 R >>\r\n", name.c_str(), no_j + i);
		fprintf(fp, "  >>\r\n");
		fprintf(fp, ">>\r\n");
		fprintf(fp, "endobj\r\n");

		fprintf(fp, "\r\n");
		AddPosInVector(fp, &objp);
		fprintf(fp, "%d 0 obj\r\n", no_c);

		char st4[100];
		int writeLen = sprintf_s(st4, sizeof(st4), "q %d 0 0 %d 0 0 cm %s Do Q\r\n", encodedSize->GetWidth(), encodedSize->GetHeight(), name.c_str());

		fprintf(fp, "<< /Length %d >>\r\n", writeLen - 2);
		fprintf(fp, "stream\r\n");
		fprintf(fp, st4);
		fprintf(fp, "endstream\r\n");
		fprintf(fp, "endobj\r\n");
	}

	for (int i = 0; i < lenImages; i++)
	{
		std::string name = "/Jpeg" + std::to_string(i + 1);

		JpegImage image(_images.at(i));
		cv::Size size = image.Size();
		EncodedImageSize* encodedSize = image.GetEncodedImageSize();

		fprintf(fp, "\r\n");
		AddPosInVector(fp, &objp);
		fprintf(fp, "%d 0 obj\r\n", no_j + i);
		fprintf(fp, "<<\r\n");
		fprintf(fp, "  /Type /XObject /Subtype /Image /Name %s\r\n", name.c_str());
		fprintf(fp, "  /Filter /DCTDecode /BitsPerComponent 8 /ColorSpace /%s\r\n", device.c_str());
		fprintf(fp, "  /Width %d /Height %d /Length %d\r\n", encodedSize->GetWidth(), encodedSize->GetHeight(), encodedSize->GetLength());
		fprintf(fp, ">>\r\n");
		fprintf(fp, "stream\r\n");

		std::vector<uchar>* jpegBuffer = image.GetJpegBuffer();
		uchar* buffer = &(*jpegBuffer)[0];
		fwrite(buffer, sizeof(uchar), jpegBuffer->size(), fp);

		fprintf(fp, "\r\n");
		fprintf(fp, "endstream\r\n");
		fprintf(fp, "endobj\r\n");
	}

	fprintf(fp, "\r\n");
	fpos_t xref;
	fgetpos(fp, &xref);

	fprintf(fp, "xref\r\n");
	int size = objp.size() + 1;
	fprintf(fp, "0 %d\r\n", size);
	fprintf(fp, "%010d %05d f\r\n", 0, 65535);
	for (int k = 0; k < objp.size(); k++)
	{
		fpos_t p = objp[k];
		fprintf(fp, "%010d %05d n\r\n", p, 0);
	}
	fprintf(fp, "trailer\r\n");
	fprintf(fp, "<< /Root 1 0 R /Size %d >>\r\n", size);
	fprintf(fp, "startxref\r\n");
	fprintf(fp, "%d\r\n", xref);
	fprintf(fp, "%%%%EOF\r\n");

	fclose(fp);

	return true;
}


void AddPosInVector(FILE* fp, std::vector<fpos_t>* positionVector)
{
	fpos_t postion;
	fgetpos(fp, &postion);
	positionVector->push_back(postion);
}