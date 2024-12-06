#pragma once
#include "Framework/Framework.h"
#include <vector>

namespace OpenAL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm();
	private: System::Windows::Forms::Button^ Play;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::ToolStrip^ toolStrip1;
	private: System::Windows::Forms::ToolStripSplitButton^ toolStripSplitButton1;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem1;
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::Button^ button4;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Play = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripSplitButton1 = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->openToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->toolStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// Play
			// 
			this->Play->Location = System::Drawing::Point(378, 494);
			this->Play->Name = L"Play";
			this->Play->Size = System::Drawing::Size(75, 23);
			this->Play->TabIndex = 0;
			this->Play->Text = L"Play";
			this->Play->UseVisualStyleBackColor = true;
			this->Play->Click += gcnew System::EventHandler(this, &MyForm::Play_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(459, 494);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Stop";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(621, 494);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Pause";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(540, 494);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Resume";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripSplitButton1 });
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(949, 25);
			this->toolStrip1->TabIndex = 4;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripSplitButton1
			// 
			this->toolStripSplitButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openToolStripMenuItem1,
					this->saveToolStripMenuItem1
			});
			this->toolStripSplitButton1->Name = L"toolStripSplitButton1";
			this->toolStripSplitButton1->Size = System::Drawing::Size(41, 22);
			this->toolStripSplitButton1->Text = L"File";
			// 
			// openToolStripMenuItem1
			// 
			this->openToolStripMenuItem1->Name = L"openToolStripMenuItem1";
			this->openToolStripMenuItem1->Size = System::Drawing::Size(180, 22);
			this->openToolStripMenuItem1->Text = L"Open";
			this->openToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem1_Click);
			// 
			// saveToolStripMenuItem1
			// 
			this->saveToolStripMenuItem1->Name = L"saveToolStripMenuItem1";
			this->saveToolStripMenuItem1->Size = System::Drawing::Size(180, 22);
			this->saveToolStripMenuItem1->Text = L"Save";
			this->saveToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::saveToolStripMenuItem1_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->openToolStripMenuItem->Text = L"Open";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(702, 494);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(219, 45);
			this->trackBar1->TabIndex = 5;
			this->trackBar1->Value = 10;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// listView1
			// 
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(12, 39);
			this->listView1->MultiSelect = false;
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(909, 375);
			this->listView1->TabIndex = 6;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listView1_SelectedIndexChanged);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(12, 494);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 7;
			this->button4->Text = L"Load sound";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(949, 546);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->Play);
			this->Name = L"MyForm";
			this->Text = L"OpenAL Tool";
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e);

	public:
		ALuint* source;
		std::vector<ALuint>* buffers;
		List<String^>^ filenames;

		ALint AddBuffer();
		System::Void ClearSounds();
		System::Void LoadSound(String^ filename);
		System::Void StartPlayback();
		System::Void StopPlayback();
		System::Void ResumePlayback();
		System::Void PausePlayback();


private: System::Void listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e);
private: System::Void Play_Click(System::Object^ sender, System::EventArgs^ e) {
	StartPlayback();
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	StopPlayback();
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	ResumePlayback();
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	PausePlayback();
}
private: System::Void openToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void saveToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e);
};
}
