#include "OpenAL.h"
#include "LoadOgg.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics;
using namespace System::IO;

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
	buffers = new std::vector<ALuint>();
	filenames = gcnew List<String^>();

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

System::Void OpenAL::MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ fileDialog = gcnew OpenFileDialog();
	fileDialog->Filter = "Ogg file|*.ogg|Wav file|*.wav";
	if (fileDialog->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		LoadSound(fileDialog->FileName);
	}
}

ALint OpenAL::MyForm::AddBuffer()
{
	ALuint buffer;
	alGenBuffers(1, &buffer);
	buffers->push_back(buffer);
	return buffer;
}

System::Void OpenAL::MyForm::ClearSounds()
{
	buffers->clear();
	filenames->Clear();
	listView1->Clear();
}

System::Void OpenAL::MyForm::LoadSound(String^ filename)
{
	std::string unmanagedFilename = toUnmanaged(filename);

	array<String^>^ filenameParts = filename->Split({ '\\' });
	if (!filenameParts->Length)
		return;
	String^ fileTitle = filenameParts[filenameParts->Length - 1];
	String^ extension = filename->Substring(filename->Length - 3);
	if (extension == "wav")
	{
		ALint buffer = AddBuffer();
		filenames->Add(filename);

		if (ALFWLoadWaveToBuffer(unmanagedFilename.data(), buffer))
		{
			listView1->Items->Add(fileTitle);
			alSourcei(*source, AL_BUFFER, buffer);
		}
	}
	else if (extension == "ogg")
	{
		ALint buffer = AddBuffer();
		filenames->Add(filename);

		if (loadOgg(buffer, unmanagedFilename))
		{
			listView1->Items->Add(fileTitle);
			alSourcei(*source, AL_BUFFER, buffer);
		}
	}
}

System::Void OpenAL::MyForm::StartPlayback()
{
	if (!listView1->SelectedIndices->Count)
		return;

	alSourceStop(*source);
	alSourcePlay(*source);
}

System::Void OpenAL::MyForm::StopPlayback()
{
	if (!listView1->SelectedIndices->Count)
		return;

	alSourceStop(*source);
}

System::Void OpenAL::MyForm::ResumePlayback()
{
	if (!listView1->SelectedIndices->Count)
		return;

	ALint state;
	alGetSourcei(*source, AL_SOURCE_STATE, &state);
	if (state == AL_PAUSED)
		alSourcePlay(*source);
}

System::Void OpenAL::MyForm::PausePlayback()
{
	if (!listView1->SelectedIndices->Count)
		return;

	alSourcePause(*source);
}

System::Void OpenAL::MyForm::listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	StopPlayback();
	if (listView1->SelectedIndices->Count)
	{
		ALint buffer = (*buffers)[listView1->SelectedIndices[0]];
		alSourcei(*source, AL_BUFFER, buffer);
	}
}

System::Void OpenAL::MyForm::trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e)
{
	alSourcef(*source, AL_GAIN, (float)trackBar1->Value / (float)trackBar1->Maximum);
}

System::Void OpenAL::MyForm::openToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ fileDialog = gcnew OpenFileDialog();
	fileDialog->Filter = "Txt file|*.txt";
	if (fileDialog->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		ClearSounds();

		StreamReader^ reader = File::OpenText(fileDialog->FileName);
		String^ line = reader->ReadLine();
		while (line != nullptr)
		{
			LoadSound(line);
			line = reader->ReadLine();
		}
		reader->Close();
	}
}

System::Void OpenAL::MyForm::saveToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ fileDialog = gcnew SaveFileDialog();
	fileDialog->Filter = "Txt file|*.txt";
	if (fileDialog->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		StreamWriter^ writer = File::CreateText(fileDialog->FileName);
		for (int i = 0; i < filenames->Count; ++i)
		{
			writer->WriteLine(filenames[i]);
		}
		writer->Close();
	}
}
