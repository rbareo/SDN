#include "EDF.hh"

/*
namespace {
  using transitions = std::array<std::array<States, 128>, (size_t) States::NUMBER_STATES>;
  using acceptings = std::array<bool, (size_t) States::NUMBER_STATES>;
  
  constexpr transitions build_transitions() {
    transitions transitions_table = {};
    
    for (size_t i = 0; i < (size_t) States::NUMBER_STATES; i++) {
      for (size_t j = 0; j < 128; j++) {
        transitions_table[i][j] = States::UNKNOWN;
      }
    }
    
    for (size_t i = (size_t) 'A'; i <= (size_t) 'Z'; i++) {
      transitions_table[(size_t) States::CHAR_START][i] = States::CHAR_BODY;
      transitions_table[(size_t) States::STRING_START][i] = States::STRING_BODY;
      transitions_table[(size_t) States::STRING_BODY][i] = States::STRING_BODY;
      
      transitions_table[(size_t) States::START][(size_t) i] = States::IDENTIFIER;
      transitions_table[(size_t) States::IDENTIFIER][(size_t) i] = States::IDENTIFIER;
    }
    
    for (size_t i = (size_t) 'a'; i <= (size_t) 'z'; i++) {
      transitions_table[(size_t) States::CHAR_START][i] = States::CHAR_BODY;
      transitions_table[(size_t) States::STRING_START][i] = States::STRING_BODY;
      transitions_table[(size_t) States::STRING_BODY][i] = States::STRING_BODY;
      
      transitions_table[(size_t) States::START][(size_t) i] = States::IDENTIFIER;
      transitions_table[(size_t) States::IDENTIFIER][(size_t) i] = States::IDENTIFIER;
    }
    
    for (size_t i = (size_t) '0'; i <= (size_t) '9'; i++) {
      transitions_table[(size_t) States::START][i] = States::INTEGER;
      transitions_table[(size_t) States::INTEGER][i] = States::INTEGER;
      
      transitions_table[(size_t) States::STRING_START][i] = States::STRING_BODY;
      transitions_table[(size_t) States::STRING_BODY][i] = States::STRING_BODY;
      
      transitions_table[(size_t) States::IDENTIFIER][(size_t) i] = States::IDENTIFIER;
    }
    
    transitions_table[(size_t) States::START][(size_t) '_'] = States::IDENTIFIER;
    transitions_table[(size_t) States::IDENTIFIER]['_'] = States::IDENTIFIER;
    
    transitions_table[(size_t) States::START][(size_t) '\''] = States::CHAR_START;
    transitions_table[(size_t) States::START][(size_t) '\"'] = States::STRING_START;
    transitions_table[(size_t) States::CHAR_BODY][(size_t) '\''] = States::CHAR_END;
    transitions_table[(size_t) States::STRING_BODY][(size_t) '\"'] = States::STRING_END;
    
    transitions_table[(size_t) States::START][(size_t) '('] = States::LEFT_PARENTHESIS;
    transitions_table[(size_t) States::START][(size_t) ')'] = States::RIGHT_PARENTHESIS;
    transitions_table[(size_t) States::START][(size_t) '['] = States::LEFT_BRACKET;
    transitions_table[(size_t) States::START][(size_t) ']'] = States::RIGHT_BRACKET;
    transitions_table[(size_t) States::START][(size_t) '{'] = States::LEFT_BRACE;
    transitions_table[(size_t) States::START][(size_t) '}'] = States::RIGHT_BRACE;
    transitions_table[(size_t) States::START][(size_t) ','] = States::COMMA;
    transitions_table[(size_t) States::START][(size_t) '@'] = States::AT;
    
    transitions_table[(size_t) States::START][(size_t) ':'] = States::COLON;
    transitions_table[(size_t) States::START][(size_t) '.'] = States::DECIMAL;

    transitions_table[(size_t) States::DECIMAL][(size_t) '.'] = States::DECIMAL_PARTIAL;
    transitions_table[(size_t) States::DECIMAL_PARTIAL][(size_t) '.'] = States::SPREAD;

    transitions_table[(size_t) States::START][(size_t) '+'] = States::PLUS;
    transitions_table[(size_t) States::START][(size_t) '-'] = States::MINUS;
    transitions_table[(size_t) States::START][(size_t) '*'] = States::MULT;
    transitions_table[(size_t) States::START][(size_t) '/'] = States::DIV;
    transitions_table[(size_t) States::START][(size_t) '%'] = States::MOD;
    
    transitions_table[(size_t) States::START][(size_t) '\n'] = States::NEWLINE;
    transitions_table[(size_t) States::START][(size_t) '\t'] = States::WHITESPACE;
    transitions_table[(size_t) States::START][(size_t) '\r'] = States::WHITESPACE;
    transitions_table[(size_t) States::START][(size_t) ' '] = States::WHITESPACE;

    transitions_table[(size_t) States::DIV][(size_t) '/'] = States::SINGLE_LINE_COMMENT;
    transitions_table[(size_t) States::DIV][(size_t) '*'] = States::MULTILINE_COMMENT_START;

    transitions_table[(size_t) States::START][(size_t) '`'] = States::TEMPLATE_START;

    transitions_table[(size_t) States::START][(size_t) '$'] = States::INTERPOLATION_PARTIAL;
    transitions_table[(size_t) States::INTERPOLATION_PARTIAL][(size_t) '{'] = States::INTERPOLATION_START;
    
    return transitions_table;
  }
  
  constexpr acceptings build_acceptings() {
    acceptings acceptings_table = {};
    
    for (size_t i = 0; i < (size_t) States::NUMBER_STATES; i++) {
      acceptings_table[i] = false;
    }
    
    acceptings_table[(size_t) States::NEWLINE] = true;
    acceptings_table[(size_t) States::WHITESPACE] = true;

    acceptings_table[(size_t) States::SINGLE_LINE_COMMENT] = true;
    acceptings_table[(size_t) States::MULTILINE_COMMENT_START] = true;
    
    acceptings_table[(size_t) States::IDENTIFIER] = true;
    acceptings_table[(size_t) States::INTEGER] = true;
    acceptings_table[(size_t) States::STRING_END] = true;
    acceptings_table[(size_t) States::CHAR_END] = true;
    
    acceptings_table[(size_t) States::LEFT_PARENTHESIS] = true;
    acceptings_table[(size_t) States::RIGHT_PARENTHESIS] = true;
    acceptings_table[(size_t) States::LEFT_BRACKET] = true;
    acceptings_table[(size_t) States::RIGHT_BRACKET] = true;
    acceptings_table[(size_t) States::LEFT_BRACE] = true;
    acceptings_table[(size_t) States::RIGHT_BRACE] = true;
    acceptings_table[(size_t) States::COMMA] = true;
    acceptings_table[(size_t) States::AT] = true;
    
    acceptings_table[(size_t) States::COLON] = true;
    acceptings_table[(size_t) States::DECIMAL] = true;
    acceptings_table[(size_t) States::SPREAD] = true;

    acceptings_table[(size_t) States::PLUS] = true;
    acceptings_table[(size_t) States::MINUS] = true;
    acceptings_table[(size_t) States::MULT] = true;
    acceptings_table[(size_t) States::DIV] = true;
    acceptings_table[(size_t) States::MOD] = true;

    acceptings_table[(size_t) States::TEMPLATE_START] = true;
    acceptings_table[(size_t) States::TEMPLATE_END] = true;
    acceptings_table[(size_t) States::INTERPOLATION_START] = true;
    acceptings_table[(size_t) States::STRING] = true;
    acceptings_table[(size_t) States::CHAR] = true;
    
    return acceptings_table;
  }

  static constexpr transitions transition_table = build_transitions();
  static constexpr acceptings acceptings_table = build_acceptings();
}

std::vector<Token> EDF::Lexer::tokenize() {
  while (position < source.size()) {
    current = source[position];
    state = transition_table[(size_t) last][(unsigned char) current];
    
    if (state == States::UNKNOWN && acceptings_table[(size_t) last]) {
      lexeme = source.substr(start_position, position - start_position);
      handle_special_states();

      if (!ignored_state) {
        tokens.push_back(Token(last, lexeme, line_number));
      }
      
      last = States::START;
      start_position = position;
      position--;
    } else if (state == States::UNKNOWN) {
      std::cerr << "ERROR: Unknown token at line " << line_number << ".\n";
      std::exit(1);
    } else {
      last = state;
    }

    position++;
  }
  
  // Final token flush
  handle_special_states();
  if (acceptings_table[(size_t) last]) {
    if (!ignored_state)
      tokens.push_back(Token(last, lexeme, line_number));
  }
  
  return tokens;
}

void EDF::Lexer::handle_special_states() {
  switch (last) {
    case States::NEWLINE:
      line_number++;
      ignored_state = true;
      return;
    case States::WHITESPACE:
      ignored_state = true;
      return;
    case States::INTERPOLATION_START:
      handle_interpolation();
      break;
    case States::STRING_END:
      lexeme = lexeme.substr(1, lexeme.length() - 2); // removes double quotes
      last = States::STRING;
      break;
    case States::CHAR_END:
      lexeme = lexeme.substr(1, lexeme.length() - 2); // removes single quotes
      last = States::CHAR;
      break;
    case States::SINGLE_LINE_COMMENT:
      ignored_state = true;
      handle_single_line_comments();
      return;
    case States::MULTILINE_COMMENT_START:
      ignored_state = true;
      handle_multiline_comments();
      return;
    default: break;
  }

  ignored_state = false;
}

void EDF::Lexer::handle_interpolation() {
  tokens.push_back(Token(States::TEMPLATE_START, "`", line_number));
  last = States::START;
  current = source[++position];
  start_position = position;

  while (current != '`') {
    state = transition_table[(size_t) last][(unsigned char) current];

    if (state == States::UNKNOWN && acceptings_table[(size_t) last]) {
      lexeme = source.substr(start_position, position - start_position);
      handle_special_states();

      if (!ignored_state) {
        tokens.push_back(Token(last, lexeme, line_number));
      }
      
      last = States::START;
      start_position = position;
      position--;
    } else if (state == States::UNKNOWN) {
      std::cerr << "ERROR: Unknown token at line " << line_number << ".\n";
      std::exit(1);
    } else {
      last = state;
    }

    current = source[++position];
  }

  position += 2; // Moves from '`' and counteracts the position-- in core loop
  last = States::TEMPLATE_END;
  lexeme = "`";
}

void EDF::Lexer::handle_single_line_comments() {
  position++;
  while (source[position] != '\n') {
    position++;
  }
}

void EDF::Lexer::handle_multiline_comments() {
  position++;
  while (source.length() > position + 2 && source[position] != '*' && source[position + 1] != '/') {
    position++;
  }
}
*/
