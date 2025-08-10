#include "display_tests.h"

// QR Code for GitHub repository using QR library
void displayQRCode()
{
    display.clearDisplay();

    // QR Code version configuration (DRY principle)
    const uint8_t QR_VERSION = 2;
    const uint8_t QR_ECC_LEVEL = 1; // ECC_MEDIUM

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
     * Current choice: Version 2 + ECC_MEDIUM + Quiet Zone
     * - Size: 25x25 modules + 4-pixel quiet zone = 33x33 total
     * - Capacity: ~40 alphanumeric chars (our URL: 52 chars = may not fit)
     * - Recovery: Can handle 15% corruption/scanning issues - good balance
     * - Colors: White modules on black background (no white background)
     * - Trade-off: Smaller size but may need to reduce ECC if URL too long
     *
     * Scanning Notes:
     * - iPhone camera may not auto-detect small QR codes (use dedicated QR apps)
     * - Turn OFF macro mode for better recognition
     * - QR scanner apps work better than built-in camera for tiny displays
     * - Hold 8-12 inches away with good lighting
     */

    // Create QR Code
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(QR_VERSION)]; // Version defined above

    // Generate QR code for GitHub repository with medium error correction
    qrcode_initText(&qrcode, qrcodeData, QR_VERSION, QR_ECC_LEVEL, QR_CODE_URL);

    // Add quiet zone (4 modules minimum around QR code per QR standard)
    uint8_t quietZone = 4;
    uint8_t totalSize = qrcode.size + (2 * quietZone);

    // Calculate positioning for centered QR code with quiet zone
    uint8_t qrStartX = (ACTUAL_WIDTH - totalSize) / 2 + quietZone;
    uint8_t qrStartY = (ACTUAL_HEIGHT - totalSize) / 2 + quietZone;

    // Draw QR code modules as WHITE on BLACK background (no white background)
    for (uint8_t y = 0; y < qrcode.size; y++)
    {
        for (uint8_t x = 0; x < qrcode.size; x++)
        {
            if (qrcode_getModule(&qrcode, x, y))
            {
                drawPixelActual(qrStartX + x, qrStartY + y, SH110X_WHITE);
            }
        }
    }

    // Add QR test label at top left (like other tests)
    setCursorActual(0, 0);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print(F("QR"));

    display.display();
}
