typedef void (*interruption_func_ptr) (const struct device*, struct gpio_callback*, uint32_t);

void hal_configure_button_interruption(struct gpio_dt_spec* button, interruption_func_ptr func, struct gpio_callback* callback_data);
void hal_setup_interruption(int, interruption_func_ptr);
void hal_interruption_init(void);
