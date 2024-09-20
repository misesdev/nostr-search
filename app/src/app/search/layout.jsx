import SearchHeader from '@/components/SearchHeader';
import './../globals.css';

export default function layout({ children }) {
    return (
        <div className="bg-gray-900">
            <SearchHeader />
            {children}
        </div>
    );
}
