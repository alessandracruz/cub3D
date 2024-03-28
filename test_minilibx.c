/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilibx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:35:21 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/26 16:58:46 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(void)
{
    void    *mlx_ptr;
    void    *win_ptr;
    int     win_width = 640;
    int     win_height = 480;

    ft_printf("Inicializando miniLibX...\n");
    mlx_ptr = mlx_init();
    if (!mlx_ptr)
    {
        ft_printf("Erro ao inicializar a miniLibX.\n");
        return (EXIT_FAILURE);
    }

    ft_printf("Criando janela...\n");
    win_ptr = mlx_new_window(mlx_ptr, win_width, win_height, "Teste miniLibX");
    if (!win_ptr)
    {
        ft_printf("Erro ao criar a janela.\n");
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        return (EXIT_FAILURE);
    }

    ft_printf("Iniciando o loop da miniLibX...\n");
    mlx_loop(mlx_ptr);
    ft_printf("Encerrando o programa...\n");

    return (EXIT_SUCCESS);
}
