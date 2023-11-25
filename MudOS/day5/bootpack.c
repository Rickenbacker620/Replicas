#define COL8_000000 0
#define COL8_FF0000 1
#define COL8_00FF00 2
#define COL8_FFFF00 3
#define COL8_0000FF 4
#define COL8_FF00FF 5
#define COL8_00FFFF 6
#define COL8_FFFFFF 7
#define COL8_C6C6C6 8
#define COL8_840000 9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void box_fill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void init_screen(unsigned char *vram, int x, int y);

struct BootInfo
{
    char cyls, leds, vmode, reserve;
    short scrnx, scrny;
    unsigned char *vram;
};

void MudMain(void)
{
    init_palette();

    unsigned char *p = (char *)0xa0000;
    struct BootInfo *binfo = (struct BootInfo *)0x0ff0;

    init_screen(binfo->vram, binfo->scrnx, binfo->scrny);

    for (;;)
    {
        io_hlt();
    }
}

void init_screen(unsigned char *vram, int x, int y)
{
    box_fill8(vram, x, COL8_008484, 0, 0, x - 1, y - 29);
    box_fill8(vram, x, COL8_C6C6C6, 0, y - 28, x - 1, y - 28);
    box_fill8(vram, x, COL8_FFFFFF, 0, y - 27, x - 1, y - 27);
    box_fill8(vram, x, COL8_C6C6C6, 0, y - 26, x - 1, y - 1);

    box_fill8(vram, x, COL8_FFFFFF, 3, y - 24, 59, y - 24);
    box_fill8(vram, x, COL8_FFFFFF, 2, y - 24, 2, y - 4);
    box_fill8(vram, x, COL8_848484, 3, y - 4, 59, y - 4);
    box_fill8(vram, x, COL8_848484, 59, y - 23, 59, y - 5);
    box_fill8(vram, x, COL8_000000, 2, y - 4, 59, y - 3);
    box_fill8(vram, x, COL8_000000, 60, y - 24, 60, y - 3);

    box_fill8(vram, x, COL8_848484, x - 47, y - 24, x - 4, y - 24);
    box_fill8(vram, x, COL8_848484, x - 47, y - 23, x - 47, y - 4);
    box_fill8(vram, x, COL8_FFFFFF, x - 47, y - 3, x - 4, y - 3);
    box_fill8(vram, x, COL8_FFFFFF, x - 3, y - 24, x - 3, y - 3);
}

void box_fill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
    for (int y = y0; y <= y1; y++)
    {
        for (int x = x0; x <= x1; x++)
        {
            vram[y * xsize + x] = c;
        }
    }
}

void init_palette(void)
{
    static unsigned char table_rgb[16 * 3] = {
        0x00, 0x00, 0x00,
        0xff, 0x00, 0x00,
        0x00, 0xff, 0x00,
        0xff, 0xff, 0x00,
        0x00, 0x00, 0xff,
        0xff, 0x00, 0xff,
        0x00, 0xff, 0xff,
        0xff, 0xff, 0xff,
        0xc6, 0xc6, 0xc6,
        0x84, 0x00, 0x00,
        0x00, 0x84, 0x00,
        0x84, 0x84, 0x00,
        0x00, 0x00, 0x84,
        0x84, 0x00, 0x84,
        0x00, 0x84, 0x84,
        0x84, 0x84, 0x84};

    set_palette(0, 15, table_rgb);
    return;
}

void set_palette(int start, int end, unsigned char *rgb)
{
    int eflags = io_load_eflags();
    io_cli();
    io_out8(0x03c8, start);
    for (int i = start; i <= end; i++)
    {
        io_out8(0x03c9, rgb[0] >> 2);
        io_out8(0x03c9, rgb[1] >> 2);
        io_out8(0x03c9, rgb[2] >> 2);
        rgb += 3;
    }
    io_store_eflags(eflags);
    return;
}
