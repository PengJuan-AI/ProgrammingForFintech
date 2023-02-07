def convert_mass(mass,current_unit,target_unit):
    """
    This program is aim to convert units of measurement for mass.
    """

    # based on kilograms
    convert_table={'Kilogram':1.0,'Pound':0.453592,'Stone':6.35029,'Jin':0.5,
                   'Seer':1.25,'Gram':0.001,'Oka':1.2829}
    
    if current_unit == 'Kilogram':
        converted = mass/convert_table[target_unit]
    else:
        # convert to kiliogram first
        m1 = mass*convert_table[current_unit]
        converted = m1/convert_table[target_unit]
    
    return converted
