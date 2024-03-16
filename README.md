# combo_town 

There are 3 modes: Alpha, Mouse, and Number.  

---  

![alpha_mode_graph](https://github.com/tomsadowski/combo_town/blob/master/documentation_assets/alpha_graph.jpg)  

Note: Capslock will also end if the mode is changed to Mouse or Number, or if Ctrl, Alt, OS, or Escape is pressed.   

---  

![mouse_mode_graph](https://github.com/tomsadowski/combo_town/blob/master/documentation_assets/mouse_graph.jpg)  

Note: Due to the left-click button, you must first access the Alpha Layer with the left thumb before accessing the Number Layer with the right thumb.

---  

![number_mode_graph](https://github.com/tomsadowski/combo_town/blob/master/documentation_assets/number_graph.jpg)  

## Combos  

Because some combos share keys, the following list of combos is shown across multiple images.    

![combos_1_of_3](https://github.com/tomsadowski/combo_town/blob/master/documentation_assets/combos_1.png) 

![combos_3_of_3](https://github.com/tomsadowski/combo_town/blob/master/documentation_assets/combos_3.png)  

![combos_2_of_3](https://github.com/tomsadowski/combo_town/blob/master/documentation_assets/combos_2.png)  

The two combos in the top row labelled L and R represent Left `mod-builder` and Right `mod-builder`.    

## Mod-Builder  

Pressing any key while a `mod-builder` combo is held down will place that keycode in a queue stored in the keyboard's memory. If there are keys in the queue and you press a key without holding a `mod-builder` combo, that keycode along with all keycodes in the queue will be sent until you release the key. This remains true even if the key you press is already in the queue. However, tapping a `mod-builder` combo without adding a keycode will clear the queue, note that a keycode will not be added if it is already in the queue. The maximum queue size is 8, adding an 8th key will result in all keycodes being sent.  

## Bonus: Game Modes   

![game_modes](https://github.com/tomsadowski/combo_town/blob/master/documentation_assets/game_modes.jpg) 
