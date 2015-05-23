#include "../include/files.hpp"

void write_header(const char * filePath, std::map<char, int> * frequencies)
{
	int headerSize = 0;
	std::ofstream outputFile;

	outputFile.open(filePath, std::ios::out | std::ios::binary);

	if(outputFile.is_open())
	{
		// Count the header size
		for(std::map<char, int>::iterator it=frequencies->begin(); it!=frequencies->end(); it++)
				headerSize++;

		// Writes on the first 4 bytes of the header the 'headerSize'		
		outputFile.write(reinterpret_cast<const char *>(&headerSize), sizeof(headerSize));

		// Writes the character and the relative frequency
		for(std::map<char, int>::iterator it=frequencies->begin(); it!=frequencies->end(); it++)
		{
			outputFile.write(reinterpret_cast<const char *>(&it->first), sizeof(it->first));
			outputFile.write(reinterpret_cast<const char *>(&it->second), sizeof(it->second));
		}

		outputFile.close();
	} else {
		char buf[256];
		std::snprintf(buf, sizeof buf, "Error: While writing header, unable to open '%s'%s", filePath, " file!");
		throw std::invalid_argument(buf);
	}
}

void read_header(const char * filePath, std::map<char, int> * frequencies)
{
	std::ifstream inputFile;

	inputFile.open(filePath, std::ios::in | std::ios::binary);

	if(inputFile.is_open())
	{
		int headerSize;
		int * integ = new int [1];
		char * charc = new char [1];

		// Reads the first 4 bytes, the headerSize
		inputFile.read(reinterpret_cast<char *>(integ), sizeof(int));
		headerSize = *integ;

		// Reads the character (char) and they frequency (int)
		for(int i = 0; i < headerSize; i++)
		{
			inputFile.read(reinterpret_cast<char *>(charc), sizeof(char));
			inputFile.read(reinterpret_cast<char *>(integ), sizeof(int));

			// Updates the 'frequencies' hashmap with the readed frequencies of the header
			(*frequencies)[*charc] = *integ;
		}

		inputFile.close();
	} else {
		char buf[256];
		std::snprintf(buf, sizeof buf, "Error: While reading header, unable to open '%s'%s", filePath, " file!");
		throw std::invalid_argument(buf);
	}
}

Files::Files(void){}

Files::~Files(void){}

// Compress initial step
int Files::readRegularFile(const char * filePath, std::vector<char> * file, std::map<char, int> * frequencies)
{
	int char_counter = 0;
	struct stat sb;
	stat(filePath, &sb);

	// Verify if the filePath passed is a regular file
	if(!S_ISREG(sb.st_mode))
	{
		char buf[256];
		std::snprintf(buf, sizeof buf, "Error: '%s'%s", filePath, " is not a regular file!");
		throw std::invalid_argument(buf);
	}

	// Open and verify if the files is open propperly
	std::ifstream inputFile;
	inputFile.open(filePath, std::ios::in | std::ios::binary);

	// If it is, fills the HashMap frequencies with characters and frequencies. Else, throw a exception
	if(inputFile.is_open())
	{
		inputFile.seekg(0, std::ios::end);
		std::size_t size = inputFile.tellg();
		inputFile.seekg(0, std::ios::beg);

		// Reads all file
		std::vector<char> v (size/sizeof(char));
		inputFile.read((char *) &v[0], size);

		// Increase the frequency of the readed symbols
		for(unsigned int i = 0; i < size; i++)
			(*frequencies)[v[i]] = (*frequencies)[v[i]] + 1;

		char_counter = size;
		(*file) = v;

		inputFile.close();
	} else {
		char buf[256];
		std::snprintf(buf, sizeof buf, "Error: Unable to open '%s'%s", filePath, " file!");
		throw std::invalid_argument(buf);
	}

	return char_counter;
}

// Extract initial step
void Files::readHuffmanFile(const char * filePath, VectorBits * characters, std::map<char, int> * frequencies)
{
	std::ifstream inputFile;
	inputFile.open(filePath, std::ios::in | std::ios::binary);

	if(inputFile.is_open())
	{
		int * integ = new int [1];
		char * charc = new char [1];

		// Reads the header and fill the frequencies HashMap
		read_header(filePath, frequencies);

		// Reads the header size and ignore it (It was already readed)
		inputFile.read(reinterpret_cast<char *>(integ), sizeof(int));
		inputFile.ignore((*integ)*5);

		while(true)
		{
			inputFile.read(reinterpret_cast<char *>(charc), sizeof(char));

			if(inputFile.eof())
				break;

			// Increase the buffer 'character' with the readed character
			(*characters).push_back(new VectorBits(*charc));
		}

		inputFile.close();
	} else {
		char buf[256];
		std::snprintf(buf, sizeof buf, "Error: Unable to open '%s'%s", filePath, " file!");
		throw std::invalid_argument(buf);
	}
}

// Extract final step
void Files::writeRegularFile(const char * filePath, Huffman * huf)
{
	std::ofstream outputFile;
	std::string filePathOutput(filePath);

	// Removes the '.huf' on the 'filePath' to create the outputFile
	outputFile.open(filePathOutput.substr(0, filePathOutput.find_last_of(".")).c_str(), std::ios::out | std::ios::binary);

	if(outputFile.is_open())
	{
		int count = 0;
		int totalFrequency = huf->getTotalFrequency();

		// While the number of processed characters are not equal to the total of the original file
		while(count != totalFrequency)
		{
			const char *co = new char(huf->readAdaptative());
			outputFile.write(co, sizeof(char));

			count++;
		}

		outputFile.close();
	} else {
		char buf[256];
		std::snprintf(buf, sizeof buf, "Error: Unable to open '%s'%s", filePath, " file!");
		throw std::invalid_argument(buf);
	}
}

// Compress final step
void Files::writeHuffmanFile(const char * filePath, Huffman * huf)
{
	std::ofstream outputFile;

	std::string filePathOutput(filePath);
	filePathOutput += ".huf";

	// Open the input and output file
	outputFile.open(filePathOutput.c_str(), std::ios::out | std::ios::binary | std::ios::app);

	if(outputFile.is_open())
	{
		VectorBits buffer;
		VectorBits * generatedCode;
		int byte;

		// Writes the header
		write_header(filePathOutput.c_str(), huf->getFrequencies());

		huf->setCurrentSize(huf->getCharCounter());

		for(unsigned int i = 0; i < huf->getFile()->size(); i++)
		{
			// Reads a character from the inpunt file storaged in memory and
			// increase the buffer of bits with the adaptativeBuilding solution
			generatedCode = huf->buildAdaptative(huf->getFile()->at(i));

			buffer.push_back(generatedCode);
			delete generatedCode;

			// While the buffer is greater than 8 bits generate bytes for the combination and put it on the output
			while(buffer.size() >= 8)
			{
				byte = buffer.generate_byte();
				const char *co = new char((char) byte);

				outputFile.write(co, sizeof(char));

				buffer.erase();
				delete co;
			}
		}

		// Completes the remaining buffer with zeros and generate the relative byte
		buffer.complete();
		byte = buffer.generate_byte();
		const char *co = new char((char) byte);

		outputFile.write(co, sizeof(char));

		outputFile.close();
		delete co;

		// Opens again the input and output file to compute the compression rate
		std::ifstream in(filePath, std::ifstream::ate | std::ifstream::binary);
		std::ifstream out(filePathOutput.c_str(), std::ifstream::ate | std::ifstream::binary);
    	
		std::clog << "  -----------------------------" << std::endl;
    std::clog << "# Compression rate: " << (double) out.tellg() / in.tellg() << std::endl; 
    	
    in.close();
		out.close();
	} else {
		char buf[256];
		std::snprintf(buf, sizeof buf, "Error: Unable to open '%s'%s", filePath, " file!");
		throw std::invalid_argument(buf);
	}
}