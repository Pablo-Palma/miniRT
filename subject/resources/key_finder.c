#include "mlx.h"
#include <stdio.h>

int key_hook(int keycode, void *param)
{
    printf("Keycode: %d\n", keycode);
    return 0;
}

int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "Keycode Finder");

    mlx_key_hook(win, key_hook, NULL);
    mlx_loop(mlx);
    return 0;
}

