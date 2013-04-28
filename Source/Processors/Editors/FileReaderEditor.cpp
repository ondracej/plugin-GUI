/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2013 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "FileReaderEditor.h"

#include "../DataThreads/FileReaderThread.h"

#include <stdio.h>

FileReaderEditor::FileReaderEditor(GenericProcessor* parentNode, FileReaderThread* thread_, bool useDefaultParameterEditors=true)
   : GenericEditor(parentNode, useDefaultParameterEditors), thread(thread_)

{
	lastFilePath = File::getCurrentWorkingDirectory();

	fileButton = new UtilityButton("Select file",Font("Small Text", 13, Font::plain));
	fileButton->addListener(this);
	fileButton->setBounds(30,50,120,25);
	addAndMakeVisible(fileButton);

 	fileNameLabel = new Label("FileNameLabel", "No file selected.");
	fileNameLabel->setBounds(20,80,140,25);
	addAndMakeVisible(fileNameLabel);

    desiredWidth = 180;

}

FileReaderEditor::~FileReaderEditor()
{

}

void FileReaderEditor::buttonEvent(Button* button)
{

	if (!acquisitionIsActive)
	{

		if (button == fileButton)
		{
			//std::cout << "Button clicked." << std::endl;
			FileChooser chooseFileReaderFile("Please select the file you want to load...",
                                          lastFilePath,
                                          "*");

	         if (chooseFileReaderFile.browseForFileToOpen())
	         {
	             // Use the selected file
	             File fileToRead(chooseFileReaderFile.getResult());

	             lastFilePath = fileToRead.getParentDirectory();

	             thread->setFile(fileToRead.getFullPathName());

	             fileNameLabel->setText(fileToRead.getFileName(),false);
			}
		}

	}
}