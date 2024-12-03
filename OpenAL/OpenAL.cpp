#include "OpenAL.h"
#include "LoadOgg.h"
#include <vector>
#include <string>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics;

[STAThreadAttribute]
void Main(array<String^>^ args) {

	ALFWInit();

	ALCdevice* device = alcOpenDevice(alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));
	if (!device)
	{
		Debug::WriteLine("unable to open default device\n");
		return;
	}

	ALCcontext* context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
	{
		Debug::WriteLine("Failed to make context current");
		return;
	}

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	OpenAL::MyForm form;
	Application::Run(% form);
}

OpenAL::MyForm::MyForm()
{
	InitializeComponent();

	source = new ALuint(0);
	buffer = new ALuint(0);

	alGenSources(1, source);
}

OpenAL::MyForm::~MyForm()
{
	if (components)
	{
		delete components;
	}
}

std::string toUnmanaged(String^ str)
{
	std::string unmanaged(str->Length, ' ');
	for (int i = 0; i < str->Length; ++i)
	{
		unmanaged[i] = str[i];
	}
	return unmanaged;
}

std::vector<char> loadFile(System::IO::Stream^ stream)
{
	std::vector<char> file(stream->Length);
	size_t i = 0;
	int byte = stream->ReadByte();
	while (byte != -1)
	{
		file[i++] = static_cast<char>(byte);
		byte = stream->ReadByte();
	}
	return file;
}

System::Void OpenAL::MyForm::openToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ fileDialog = gcnew OpenFileDialog();
	fileDialog->Filter = "Ogg file|*.ogg|Wav file|*.wav";
	if (fileDialog->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		alDeleteBuffers(1, buffer);
		alGenBuffers(1, buffer);
		
		String^ extension = fileDialog->FileName->Substring(fileDialog->FileName->Length - 3);
		if (extension == "wav")
		{
			std::string unmanagedFilename = toUnmanaged(fileDialog->FileName);
			
			if (ALFWLoadWaveToBuffer(unmanagedFilename.data(), *buffer))
			{
				alSourcei(*source, AL_BUFFER, *buffer);
				alSourcePlay(*source);
			}
		}
		else if (extension == "ogg")
		{
			/*IntPtr filenamePtr = Marshal::StringToHGlobalAnsi(fileDialog->FileName);
			const char* filename = (char*)(void*)filenamePtr;*/
			std::string unmanagedFilename = toUnmanaged(fileDialog->FileName);
			
			FILE* file = fopen(unmanagedFilename.data(), "rb");
			loadOgg(*buffer, file);
			fclose(file);

			alSourcei(*source, AL_BUFFER, *buffer);
			alSourcePlay(*source);

			//Marshal::FreeHGlobal(filenamePtr);
		}
	}
}
