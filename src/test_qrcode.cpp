#include "display_tests.h"

// QR Code for GitHub repository using QR library
void displayQRCode()
{
    display.clearDisplay();

    /*
     * QR Code Configuration Balance:
     *
     * Version (Size) vs URL Length vs Error Correction Trade-offs:
     *
     * Version 3 (29x29): ~84 alphanumeric chars (ECC_LOW) - short URLs
     * Version 4 (33x33): ~114 alphanumeric chars (ECC_LOW) - longer URLs
     * Version 5 (37x37): ~134 alphanumeric chars (ECC_LOW) - maximum for 72x40 display
     *
     * Error Correction Levels (reduces capacity but improves reliability):
     * ECC_LOW (0):       ~7% error recovery  - maximum data capacity
     * ECC_MEDIUM (1):    ~15% error recovery - good balance
     * ECC_QUARTILE (2):  ~25% error recovery - robust scanning
     * ECC_HIGH (3):      ~30% error recovery - maximum reliability
     *
     * Current choice: Version 4 + ECC_MEDIUM + Quiet Zone
     * - Size: 33x33 modules + 4-pixel quiet zone = 41x41 total
     * - Capacity: ~78 alphanumeric chars (our URL: 52 chars = 67% usage)
     * - Recovery: Can handle 15% corruption/scanning issues
     * - Colors: Black modules on white background (standard)
     * - Trade-off: iPhone-optimized for better recognition
     *
     * Scanning Notes:
     * - iPhone camera may not auto-detect small QR codes (use dedicated QR apps)
     * - Turn OFF macro mode for better recognition
     * - QR scanner apps work better than built-in camera for tiny displays
     * - Hold 8-12 inches away with good lighting
     */

    // Create QR Code
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(4)]; // Version 4 QR code

    // Generate QR code for GitHub repository
    qrcode_initText(&qrcode, qrcodeData, 4, 1, "https://github.com/Pharkie/ESP32-C3-OLED-Demo");

    // Add quiet zone (4 modules minimum around QR code per QR standard)
    uint8_t quietZone = 4;
    uint8_t totalSize = qrcode.size + (2 * quietZone);

    // Calculate positioning for centered QR code with quiet zone
    uint8_t qrStartX = (ACTUAL_WIDTH - totalSize) / 2 + quietZone;
    uint8_t qrStartY = (ACTUAL_HEIGHT - totalSize) / 2 + quietZone;

    // Draw white background for quiet zone (required for QR recognition)
    fillRectActual((ACTUAL_WIDTH - totalSize) / 2, (ACTUAL_HEIGHT - totalSize) / 2,
                   totalSize, totalSize, SH110X_WHITE);

    // Draw QR code modules as BLACK on WHITE background (standard convention)
    for (uint8_t y = 0; y < qrcode.size; y++)
    {
        for (uint8_t x = 0; x < qrcode.size; x++)
        {
            if (qrcode_getModule(&qrcode, x, y))
            {
                drawPixelActual(qrStartX + x, qrStartY + y, SH110X_BLACK);
            }
        }
    }

    display.display();
}
