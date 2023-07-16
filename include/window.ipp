// Safely connect functions to signals, and also print the object name on signal
// use it like this:
//     safe_connect_signal(widget, widget->signal_something(), [...](){...});
template <typename WidgetClass, typename SignalType, typename Function>
void safe_connect_signal(WidgetClass* widget, SignalType signal, const Function& call_function) {
    if (widget) {
        const Glib::ustring content = widget->get_name();
        signal.connect([content, call_function]() {
            #ifdef DEBUG
            std::cout << "Debug: Activated widget \"" << content << "\"." << std::endl;
            #endif
            call_function();
        });
    }
}