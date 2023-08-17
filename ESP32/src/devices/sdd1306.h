// most recently displayed values
String previousLocalTime = "";
String previousLocalTemp = "";

void displayText(String text, int x, int y, int size, const GFXfont* font) {
  display.setFont(font);
  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x,y);
  display.println(text);
  display.display();
}