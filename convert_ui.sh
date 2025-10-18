#!/bin/bash
# Read the UI file and create a proper C string
echo '#ifndef MAIN_UI_H' > main_ui.h
echo '#define MAIN_UI_H' >> main_ui.h
echo '' >> main_ui.h
echo 'const char *main_ui_xml = ' >> main_ui.h

# Process each line of the UI file
while IFS= read -r line; do
    # Escape backslashes and quotes
    escaped_line=$(echo "$line" | sed 's/\\/\\\\/g' | sed 's/"/\\"/g')
    echo "\"$escaped_line\\n\"" >> main_ui.h
done < main.ui

echo ';' >> main_ui.h
echo '' >> main_ui.h
echo '#endif /* MAIN_UI_H */' >> main_ui.h

echo "main_ui.h generated successfully!"
