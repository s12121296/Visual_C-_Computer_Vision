#pragma once
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <iostream>

namespace WindowsApplication1
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// MyForm ���K�n
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  �b���[�J�غc�禡�{���X
			//
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button2;
	protected:



	protected:

	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(128, 673);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(107, 44);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Open Image";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(37, 24);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(533, 464);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(398, 673);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(107, 44);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Median Filter";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(672, 743);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		//�ŧiBitmap �x�s�}�Ҫ���
		Bitmap^ image1;

		//�ŧi���@BitmapData���A ��ܹ�����m
		Imaging::BitmapData ^ ImageData1;

		//�ŧi�Ϲ��ϰ�(�]�w����Ū���B���ץ����Ϲ��ϰ�)
		Rectangle rect;

#pragma endregion
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {

		//new�@�ӷs��openFileDialog1�}���ɮ�
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		//�]�wFilter�A�ΥH���w�ϥΪ̶}�Ҫ��ɮ�
		openFileDialog1->Filter = "�I�}�� (*.bmp)| *.bmp| All files (*.*)| *.*";
		//�w�]�ɮצW�٬��ŭ�
		openFileDialog1->FileName = "";
		//�]�w���X��ܵ��������D�W��
		openFileDialog1->Title = "���J�v��";
		//�]�wFilter��ܼҦ�(�̷�Filter�ơA�p���ҿ��1��ܰ_�l�X�{�����I�}�ϡA���2���All filts)
	    openFileDialog1->FilterIndex = 1;


		//���X�ɮ׿�ܵ���(ShowDialog)�A�åB�p�G�ϥΪ��I���ɮסA�åB�ɮצW�ٶW�L0�Ӧr���A�h�P�_�O��True�A�i�J�B�z�{��
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0)
		{
			//�N������ɮ�Ū���åB�s��Image1
			image1 = safe_cast<Bitmap^>(Image::FromFile(openFileDialog1->FileName));
			//�]�wrect�d��j�p
			rect = Rectangle(0, 0, image1->Width, image1->Height);
			//�N�v����ܦbpictureBox1
			pictureBox1->Image = image1;
		}
	}
	//Median Filter
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		////�Ȧs�ϪŶ�
		Bitmap ^ temp_Image;
		temp_Image = gcnew Bitmap(image1->Width, image1->Height); //�ͦ��@�i���e��image�@�˪�Bitmap

		Imaging::BitmapData ^ temp_Image_Data;
		temp_Image_Data = temp_Image->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image1->PixelFormat);
		
		IntPtr ptr, temp_Ptr;
		temp_Ptr = temp_Image_Data->Scan0;  //�Nint���Ы��VImage������ƪ��̫e����m
		Byte* q = (Byte*)((Void*)temp_Ptr); //�]�w����

		////��ϪŶ�
		ImageData1 = image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image1->PixelFormat);
		ptr = ImageData1->Scan0; //�Nint���Ы��VImage������ƪ��̫e����m
		Byte* p = (Byte*)((Void*)ptr); //�]�w����

		//���а}�C
		Byte* r[9]; 

		//�x�s�����P��m�s���}�C
		int Array[2][9] = { 0 };
		int temp[2];

		//�s���Ҧ������I�A���ι����A�B�z�����ϰ�
		for (int y = 0; y < image1->Height; y++) {
			for (int x = 0; x < image1->Width; x++) {

				//�̥~�򹳯����B�z
				if (y > 0 && x > 0 && y < image1->Height - 1 && x < image1->Width - 1)
				{

					int Masksize = 0;
					//�M�X3X3�B�n���E�ӹ��� �ñN�����Ȧs�U��
					for (int i = -1; i <= 1; i++)
					{
						for (int j = -3; j <= 3; j += 3)
						{
							//���Ы��V�ؼй�����}
							r[Masksize] = (Byte*)(Void*)p + i * image1->Width * 3 + j;
							//�x�s����
							Array[0][Masksize] = r[Masksize][0] + r[Masksize][1] + r[Masksize][2];
							//�x�s�����s��
							Array[1][Masksize] = Masksize;
							Masksize++;
						}
					}

					int min;
					//�u�ƨ�Ĥ��� �]���Ĥ��ӴN�O����� ���Υ����Ƨ�
					for (int n = 0; n < 5; ++n)
					{
						min = n;
						//�ϥή�w�ƧǪk
						for (int o = n + 1; o < 9; ++o)
						{
							if (Array[0][o] < Array[0][min])
								min = o;
							
						}
						//temp�Ȧs�����P�s��
						temp[0] = Array[0][n];
						temp[1] = Array[1][n];

						//�N���p�������ȻP�s���h��ثe�B�z�쪺��mn
						Array[0][n] = Array[0][min];
						Array[1][n] = Array[1][min];

						//�Ntemp��^�h ��swap�洫
						Array[0][min] = temp[0];
						Array[1][min] = temp[1];
					}

					//���Ƨǧ���5�ӹ����ȱo���Ц�} �N��}��B G R���ثe����
					q[0] = r[Array[1][4]][0];
					q[1] = r[Array[1][4]][1];
					q[2] = r[Array[1][4]][2];
				}
				else
				{
					q[0] = p[0];
					q[1] = p[1];
					q[2] = p[2];
				}
				q += 3;
				p += 3;
			}
		}

		//���깳����m
		image1->UnlockBits(ImageData1);
		temp_Image->UnlockBits(temp_Image_Data);
		//��ܦbPictureBox�W
		pictureBox1->Image = temp_Image;
	}
};
}