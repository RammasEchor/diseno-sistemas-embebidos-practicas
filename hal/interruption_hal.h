typedef void (*interruption_func_ptr) (const struct device*, struct gpio_callback*, uint32_t);

void config_button_interruption_function(struct gpio_dt_spec* button, interruption_func_ptr func, struct gpio_callback* callback_data);
void hal_setup_interruption(struct gpio_dt_spec* button_spec, interruption_func_ptr func);
