typedef void (*interruption_func_ptr) (const struct device*, struct gpio_callback*, uint32_t);

void hal_configure_button_interruption();
void hal_setup_interruption(int, interruption_func_ptr);
void hal_interruption_init(void);
