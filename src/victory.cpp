#include "victory.h"

Victory::Victory() {}

Victory::Victory(Graphics* g, Input* i, FontManager* fm) {
	graphics = g;
	input = i;
	baseFm = fm;
}

Victory::~Victory() {}

void Victory::initialize() {
	D3DXCreateLine(graphics->get3Ddevice(), &textBox);
	textBox->SetWidth(victoryNS::tbLineWidth);

	D3DXCreateLine(graphics->get3Ddevice(), &cursor);
	cursor->SetWidth(victoryNS::cursorLineWidth);
}

void Victory::update(float frameTime) {}

void Victory::render() {
	std::string tbValue = toUpperCase(input->getTextIn());

	VECTOR2 tbPoints[victoryNS::tbPointsToDraw] = {victoryNS::tbTopLeft, victoryNS::tbTopRight, 
		victoryNS::tbBottomRight, victoryNS::tbBottomLeft, victoryNS::tbTopLeft};

	textBox->Begin();
	textBox->Draw(tbPoints, victoryNS::tbPointsToDraw, graphicsNS::WHITE);
	textBox->End();

	int totalWidth = baseFm->getTotalWidth(fontNS::SABO_FILLED, tbValue);
	
	// check if tbValue fits tb
	while (totalWidth > victoryNS::tbWidth - victoryNS::tbPadding * 2) {
		// shrink text
		tbValue.erase(tbValue.begin());
		totalWidth = baseFm->getTotalWidth(fontNS::SABO_FILLED, tbValue);
	}
	

	baseFm->print(fontNS::SABO_FILLED, fontNS::WHITE, victoryNS::textStartX, victoryNS::textStartY, tbValue);

	VECTOR2 cursorTop = victoryNS::cursorStartTop + VECTOR2(totalWidth + victoryNS::cursorPadding, 0);
	VECTOR2 cursorBottom = victoryNS::cursorStartBottom + VECTOR2(totalWidth + victoryNS::cursorPadding, 0);
	VECTOR2 cursorPoints[victoryNS::cursorPointsToDraw] = { cursorTop, cursorBottom };

	cursor->Begin();
	cursor->Draw(cursorPoints, victoryNS::cursorPointsToDraw, graphicsNS::WHITE);
	cursor->End();

	printf("%s\n", input->getTextIn().c_str());
	if (input->wasKeyPressed(ENTER_KEY))
		input->clearTextIn();
}

void Victory::releaseAll() {
	textBox->OnLostDevice();
}

void Victory::resetAll() {
	textBox->OnResetDevice();
}	
