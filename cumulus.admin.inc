<?php
/**
 * Implements hook_menu().
 */

/**
 * Implements hook_settings().
 */
function cumulus_admin_settings($form, &$form_state) {
  $form['#config'] = 'cumulus.settings';
  $form['settings'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Clear the Cumulus cache'),
    '#description' => t('If you see older terms, or are unable to see terms from newly added vocabularies, try clearing the cache.<br />This will only clear the Cumulus related data from the cache. It will not clear the full Drupal cache.'),
  );
  $form['settings']['clear_cache'] = array(
    '#type' => 'submit',
    '#value' => t('Click to clear'),
    '#submit' => array('cumulus_clear_cache'),
  );

  return system_settings_form($form);
}

/**
 * Implements hook_block_configure().
 */
function cumulus_configure_form($form, $settings) {
  $config = $settings;

  // Merge in the default configuration.
  $config += cumulus_default_config();

  $vocab_options = array();
  foreach (taxonomy_vocabulary_load_multiple(FALSE) as $machine => $vocab) {
    $vocab_options[$machine] = check_plain($vocab->name);
  }
  $form['vocabs'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Vocabularies to include'),
    '#options' => $vocab_options,
    '#default_value' => $config['vocabs'],
  );

  $form['tagadelic_step'] = array(
    '#type' => 'number',
    '#title' => t('Tag size interval'),
    '#default_value' => $config['tagadelic_step'],
    '#description' => t('The number of tag sizes you want to use.'),
  );

  $form['tagadelic_limit'] = array(
    '#type' => 'number',
    '#title' => t('Number of tags to display'),
    '#default_value' => $config['tagadelic_limit'],
    '#description' => t('The maximum number of tags that will be displayed.'),
  );

  $form['flash_width'] = array(
    '#type' => 'number',
    '#title' => t('Width of cumulus'),
    '#default_value' => $config['flash_width'],

  );

  $form['flash_height'] = array(
    '#type' => 'number',
    '#title' => t('Height of cumulus'),
    '#default_value' => $config['flash_height'],
    '#field_suffix' => t('pixels'),
  );

  $form['flash_background'] = array(
    '#type' => 'textfield',
    '#title' => t('Background color of cumulus'),
    '#default_value' => $config['flash_background'],
    '#field_prefix' => '#',
    '#maxlength' => 6,
    '#description' => t('The hex color value for the background of the cumulus. E.g. ffffff. If "Background transparency" is enabled, this option will have no effect.'),
  );

  $form['flash_transparency'] = array(
    '#type' => 'select',
    '#title' => t('Background transparency'),
    '#default_value' => $config['flash_transparency'],
    '#options' => array(
      'false' => t('no'),
      'true' => t('yes'),
    ),
    '#description' => t('Enabling background transparency might cause issues with some (mostly older) browsers. Under Linux, transparency doesn\'t work at all due to a known limitation in the current Flash player.'),
  );

  $form['flash_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Font color of cumulus'),
    '#default_value' => $config['flash_color'],
    '#field_prefix' => '#',
    '#maxlength' => 6,
    '#description' => t('The hex color value you would like to use for the tags. E.g. 000000.'),
  );

  $form['flash_color2'] = array(
    '#type' => 'textfield',
    '#title' => t('Second font color of cumulus'),
    '#default_value' => $config['flash_color2'],
    '#field_prefix' => '#',
    '#maxlength' => 6,
    '#description' => t('Second tag color. If supplied, tags will get a color from a gradient between both colors based on their popularity.'),
  );

  $form['flash_hicolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Highlight color of cumulus'),
    '#default_value' => $config['flash_hicolor'],
    '#field_prefix' => '#',
    '#maxlength' => 6,
    '#description' => t('The hex color value you would like to use for the tag mouseover/hover color'),
  );

  $form['flash_speed'] = array(
    '#type' => 'number',
    '#title' => t('Rotation speed'),
    '#default_value' => $config['flash_speed'],
    '#maxlength' => 3,
    '#description' => t('Set the speed of the cumulus. Options between 25 and 500 work best.'),
  );

  $form['flash_distribute'] = array(
    '#type' => 'select',
    '#title' => t('Distribute tags evenly on cumulus'),
    '#default_value' => $config['flash_distribute'],
    '#options' => array(
      'false' => t('no'),
      'true' => t('yes'),
    ),
    '#description' => t('When enabled, the movie will attempt to distribute the tags evenly over the surface of the cumulus.'),
  );

  $form['flash_font_size'] = array(
    '#type' => 'number',
    '#title' => t('Font size'),
    '#default_value' => $config['flash_font_size'],
    '#maxlength' => 2,
    '#description' => t('Set the font size of the tag with the lowest tag-size in pixels (level 1).'),
  );
  $form['flash_font_size_interval'] = array(
    '#type' => 'number',
    '#title' => t('Font size interval'),
    '#default_value' => $config['flash_font_size_interval'],
    '#maxlength' => 1,
    '#description' => t('Set the font size interval used for the different tag-sizes (level 2 and higher).'),
  );

  return $form;
}
