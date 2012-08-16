<?php

/**
 * Field handler to provide a human-readable version of the stored serialized combination of attributes
 */
class noderecommendation_handler_field_data extends views_handler_field {
  function render($values) {
    $value = $values->{$this->field_alias};
    if ($value) {
      $recommendation = unserialize($value);
      $info =_noderecommendation_to_arrayinfo($recommendation);
      return theme('noderecommendation_defaults', $info);
    }
  }
}